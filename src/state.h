#pragma once

#include <iostream>
#include <string>
#include "message.h"

class State{
  public:
    virtual bool accept(Message msg){
      return false;
    }

    virtual void onEntry(){
    }
    
    void setName(std::string name){
      name_ = name;
    }

    std::string getName(){
      return name_;
    }

  private:
    std::string name_;
};
