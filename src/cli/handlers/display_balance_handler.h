#pragma once

#include <iostream>
#include "message_handler.h"
#include "message.h"

class DisplayBalanceHandler: public MessageHandler{
  public:
    DisplayBalanceHandler(std::shared_ptr<MessageSender> sender,
      std::shared_ptr<StateMachine> state_machine){
      setName("DisplayBalanceHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      std::cout << "Balance is " << msg.getBody() << std::endl;
      state_machine_->transition("CLIStartState");
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};

