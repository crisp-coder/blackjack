#pragma once

#include "state.h"
class QuitState: public State{
  public:
    QuitState(){
      setName("QuitState");
    }

    void onEntry(){
      logger.LOG(bjlogger::INFO, "Entering quit state..");
    }

    bool accept(Message msg){
      return false;
    }
};

