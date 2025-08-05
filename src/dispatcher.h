#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "message.h"
#include "message_handler.h"
#include "state_machine.h"

#include "bjlogger.h"

class Dispatcher{
  public:
    Dispatcher(std::shared_ptr<StateMachine> state_machine){
      state_machine_ = state_machine;
    }

    void dispatch(Message msg){
      if(state_machine_->getCurrentState()->accept(msg)){
        auto handlers = msg_to_handlers_[msg.getName()];
        for(auto h : handlers){
          h->handle(msg);
        }
      }
      else{
        logger.LOG(bjlogger::ERROR, "Dispatcher:: no handler found for " + msg.getName());
      }
    }

    void registerHandler(Message msg, std::shared_ptr<MessageHandler> handler){
      msg_to_handlers_[msg.getName()].push_back(handler);
    }

  private:
    std::map<std::string, std::vector<std::shared_ptr<MessageHandler>>> msg_to_handlers_;
    std::shared_ptr<StateMachine> state_machine_;
};

