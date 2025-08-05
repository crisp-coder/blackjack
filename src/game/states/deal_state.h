#pragma once

#include "state.h"
#include "message.h"
#include "message_sender.h"
#include "game/messages/to_player/table_data_message.h"

class DealState : public State{
  public:
    DealState(std::shared_ptr<MessageSender> message_sender,
              std::shared_ptr<StateMachine> state_machine,
              std::shared_ptr<Table> table){
      state_machine_ = state_machine;
      message_sender_ = message_sender;
      table_ = table;
      setName("DealState");
    }

    bool accept(Message msg){
      return false;
    }

    void onEntry(){
      table_->dealCardToPlayer(true);
      table_->dealCardToDealer(false);
      table_->dealCardToPlayer(true);
      table_->dealCardToDealer(true);

      TableDataMessage table_data_msg("Player", table_->encode());
      message_sender_->sendMessage(table_data_msg);

      if(table_->playerCanInsure()){
        state_machine_->transition("InsuranceState");
      }
      else if(table_->checkPlayerNatural()){
        state_machine_->transition("DealerTurnState");
      }
      else{
        state_machine_->transition("PlayerTurnState");
      }
    }

  private:
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<Table> table_;
};


