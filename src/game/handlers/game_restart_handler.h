#pragma once

#include "message.h"

class GameRestartHandler : public MessageHandler{
  public:
    GameRestartHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Table> table){
      setName("GameRestartHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    void handle(Message msg){
      table_->reset();
      state_machine_->transition("GameStartState");
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Table> table_;
};

