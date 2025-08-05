#pragma once

#include <iostream>
#include "message_handler.h"
#include "message.h"
#include "utils.h"

class DisplayTableHandler: public MessageHandler{
  public:
    DisplayTableHandler(std::shared_ptr<MessageSender> sender,
      std::shared_ptr<StateMachine> state_machine){
      setName("DisplayTableHandler");
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

