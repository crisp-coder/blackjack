#pragma once

#include "message_handler.h"
#include "message.h"

class RestartHandler: public MessageHandler{
  public:
    RestartHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine){
      setName("RestartHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      state_machine_->transition("CLIStartState");
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};

