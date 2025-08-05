#pragma once

#include "state.h"
#include "message.h"
#include "game/messages/to_player/table_data_message.h"

class DealerTurnState : public State{
  public:
    DealerTurnState(std::shared_ptr<MessageSender> message_sender,
                   std::shared_ptr<StateMachine> state_machine,
                   std::shared_ptr<Table> table){
      setName("DealerTurnState");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    bool accept(Message msg){
      return false;
    }

    void onEntry(){
      table_->setDealerHoleCardFaceUp();

      if(table_->pollHands()){
        while(table_->dealerCanDraw()){
          table_->dealCardToDealer(true);
        }
      }

      TableDataMessage table_data_msg("Player", table_->encode());
      message_sender_->sendMessage(table_data_msg);

      state_machine_->transition("ShowdownState");
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Table> table_;
};

