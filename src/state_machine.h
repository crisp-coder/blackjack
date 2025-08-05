#pragma once

#include "state.h"

class StateMachine{
  public:
    StateMachine(){}

    void setCurrentState(std::shared_ptr<State> state){
      current_state_ = state;
    }

    void transition(std::shared_ptr<State> state){
      logger.LOG(bjlogger::INFO, name_ + ": transition to " + state->getName());
      setCurrentState(state);
      state->onEntry();
    }

    void transition(std::string name){
      transition(states_[name]);
    }

    std::shared_ptr<State> getCurrentState(){
      return current_state_;
    }

    void registerState(std::shared_ptr<State> state){
      states_[state->getName()] = state;
    }

    std::string getName(){
      return name_;
    }

    void setName(std::string name){
      name_ = name;
    }

  private:
    std::shared_ptr<State> current_state_;
    std::map<std::string, std::shared_ptr<State>> states_;
    std::string name_;
};
