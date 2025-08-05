#pragma once

#include "message_handler.h"
#include "message.h"

class StandHandler : public MessageHandler{
  public:
    StandHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Table> table){
      setName("StandHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    void handle(Message msg){
      if(!table_->nextHand()){
        state_machine_->transition("DealerTurnState");
      }
      else{
        state_machine_->transition("PlayerTurnState");
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Table> table_;
};

