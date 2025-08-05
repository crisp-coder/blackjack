#pragma once

#include "state.h"

class PlayingHandState: public State{
  public:
    PlayingHandState(std::shared_ptr<MessageSender> message_sender,
                     std::shared_ptr<StateMachine> state_machine){
      setName("PlayingHandState");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
    }

    bool accept(Message msg){
      std::string name = msg.getName();
      return name == "QuitMessage" || 
             name == "RestartMessage" ||
             name == "InsufficientFundsMessage"||
             name == "DisplayTableMessage" ||
             name == "DisplayBalanceMessage"||
             name == "DisplayHandResultMessage" ||
             name == "DisplayInsuranceResultMessage" ||
             name == "RequestInputMessage" ||
             name == "CLIRoundCompletedMessage"||
             name == "RequestInsuranceMessage";
    }

    void onEntry(){
    }

    private:
     std::shared_ptr<MessageSender> message_sender_;
     std::shared_ptr<StateMachine> state_machine_;
};

