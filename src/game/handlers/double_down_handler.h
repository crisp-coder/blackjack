#pragma once

#include <string>
#include <iostream>
#include "message_handler.h"
#include "message.h"
#include "game/messages/to_player/table_data_message.h"
#include "utils.h"

class DoubleDownHandler : public MessageHandler{
  public:
    DoubleDownHandler(std::shared_ptr<MessageSender> message_sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Table> table){
      setName("DoubleDownHandler");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    void handle(Message msg){
      table_->setPlayerWager(table_->getPlayerWager()*2);
      table_->dealCardToPlayer(true);
      TableDataMessage table_data_msg("Player", table_->encode());
      message_sender_->sendMessage(table_data_msg);

      if(table_->checkPlayerBust() || table_->checkPlayerHas21()){
        if(table_->nextHand()){
          state_machine_->transition("PlayerTurnState");
        }
        else{
          state_machine_->transition("DealerTurnState");
        }
      }
      else{
        state_machine_->transition("DealerTurnState");
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Table> table_;
};

