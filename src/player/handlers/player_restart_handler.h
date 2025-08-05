#pragma once

#include "message.h"
#include "message_handler.h"

class PlayerRestartHandler : public MessageHandler{
  public:
    PlayerRestartHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine){
        setName("PlayerRestartHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      state_machine_->transition("PlayerStartState");
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};
