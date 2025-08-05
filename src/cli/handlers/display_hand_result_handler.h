#pragma once

#include <iostream>
#include "message_handler.h"
#include "message.h"
#include "utils.h"

class DisplayHandResultHandler: public MessageHandler{
  public:
    DisplayHandResultHandler(std::shared_ptr<MessageSender> sender,
      std::shared_ptr<StateMachine> state_machine){
      setName("DisplayHandResultHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      std::cout << msg.getBody() << std::endl;
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};

