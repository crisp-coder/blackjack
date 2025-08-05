#pragma once

#include "message_handler.h"
#include "message.h"
#include "game/messages/to_player/table_data_message.h"

class SplitHandler : public MessageHandler{
  public:
    SplitHandler(std::shared_ptr<MessageSender> message_sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Table> table){
      setName("SplitHandler");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    void handle(Message msg){
      table_->splitPlayerHand();
      TableDataMessage table_data_msg("Player", table_->encode());
      message_sender_->sendMessage(table_data_msg);
      state_machine_->transition("PlayerTurnState");
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Table> table_;
};

