#pragma once

#include "message_handler.h"
#include "message.h"

class SurrenderHandler : public MessageHandler{
  public:
    SurrenderHandler(std::shared_ptr<MessageSender> message_sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Table> table){
      setName("SurrenderHandler");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    void handle(Message msg){
      table_->surrenderPlayerHand(); 
      if(table_->nextHand()){
        state_machine_->transition("PlayerTurnState");
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

