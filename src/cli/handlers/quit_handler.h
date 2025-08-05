#pragma once

#include "message_handler.h"
#include "message.h"

class QuitHandler : public MessageHandler {
  public:
    QuitHandler(std::shared_ptr<MessageSender> sender, std::shared_ptr<StateMachine> state_machine){
      setName("QuitHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      state_machine_->transition("QuitState");
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;

};
