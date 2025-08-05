#pragma once

#include <string>
#include "message.h"

class MessageHandler{
  public:
    virtual void handle(Message msg){
      // do nothing
    }
    
    std::string getName(){
      return name_;
    }

    void setName(std::string name){
      name_ = name;
    }

  private:
    std::string name_;
};

