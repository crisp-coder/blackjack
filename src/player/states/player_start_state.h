#pragma once

#include "state.h"
#include "message.h"

class PlayerStartState : public State{
  public:
    PlayerStartState(){
        setName("PlayerStartState");
      }

    bool accept(Message msg){
      std::string name = msg.getName();
      return name == "PlayHandMessage" ||
             name == "CashInMessage" ||
             name == "ChangeWagerMessage" ||
             name == "CheckBalanceMessage" ||
             name == "QuitMessage" ||
             name == "RestartMessage" ||
             name == "WagerResponseMessage";
    }

    void onEntry(){
    }
};


