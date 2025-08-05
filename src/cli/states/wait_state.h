#pragma once

#include "state.h"

class WaitState : public State{
  public:
    WaitState(){
      setName("WaitState");
    }

    bool accept(Message msg){
      std::string name = msg.getName();
      return name == "ChangeWagerResponseMessage" ||
             name == "CashInResponseMessage" ||
             name == "PlayResponseMessage" ||
             name == "InputResponseMessage";
    }

    void onEntry(){
    }
};

