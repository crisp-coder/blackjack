#pragma once

#include "message.h"
#include "message_handler.h"
#include "player/messages/to_interface/display_table_message.h"

class TableDataHandler : public MessageHandler{
  public:
    TableDataHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine){
        setName("TableDataHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      DisplayTableMessage display_table_msg("CLI", msg.getBody());
      message_sender_->sendMessage(display_table_msg);
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};
