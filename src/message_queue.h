#pragma once

#include <queue>
#include "message.h"

class MessageQueue{
  public:
    MessageQueue(){}
 
    Message getMessage(){
      Message msg = queue_.front();
      queue_.pop();
      return msg;
    }

    void push(Message message){
      queue_.push(message);
    }

    bool empty(){
      return queue_.empty();
    }

  private:
    std::queue<Message> queue_;
};

