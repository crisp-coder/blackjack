#pragma once

#include "state.h"
#include "message.h"

class WagerState : public State{
  public:
    WagerState(std::shared_ptr<MessageSender> message_sender,
                   std::shared_ptr<StateMachine> state_machine,
                   std::shared_ptr<Table> table){
      setName("WagerState");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    bool accept(Message msg){
      std::string name = msg.getName();
      return name == "RestartMessage" ||
        name == "QuitMessage";
    }


    void onEntry(){
    }

    private:
      std::shared_ptr<MessageSender> message_sender_;
      std::shared_ptr<StateMachine> state_machine_;
      std::shared_ptr<Table> table_;
};

