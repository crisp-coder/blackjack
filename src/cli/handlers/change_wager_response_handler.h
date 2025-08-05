#pragma once

#include "message.h"
#include "message_sender.h"
#include "message_handler.h"
#include "state_machine.h"

class ChangeWagerResponseHandler: public MessageHandler{
  public:
    ChangeWagerResponseHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine){
      setName("ChangeWagerResponseHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      if(msg.getBody() == "Accepted"){
        state_machine_->transition("CLIStartState");
      }
      else if(msg.getBody() == "Rejected"){
        state_machine_->transition("CLIStartState");
      }
      else{
        logger.LOG(bjlogger::ERROR, "CLI:ChangeWagerResponseHandler: received bad message.");
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};

