#pragma once

#include <string>
#include "state.h"
#include "message.h"

class GameStartState : public State{
  public:
    GameStartState(std::shared_ptr<MessageSender> message_sender,
                   std::shared_ptr<StateMachine> state_machine,
                   std::shared_ptr<Table> table){
      setName("GameStartState");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    bool accept(Message msg){
      std::string name = msg.getName();
      return name == "WagerMessage" ||
        name == "RestartMessage" ||
        name == "QuitMessage";
    }

    void onEntry(){
      table_->clearHands();
      table_->resetIndex();
      if(table_->isTimeToShuffle()){
        table_->shuffleDeck();
      }
    }

    private:
      std::shared_ptr<MessageSender> message_sender_;
      std::shared_ptr<StateMachine> state_machine_;
      std::shared_ptr<Table> table_;
};

