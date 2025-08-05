#pragma once

#include "message.h"
#include "message_handler.h"
#include "player/messages/to_interface/request_input_message.h"

class PlayerChoiceHandler : public MessageHandler{
  public:
    PlayerChoiceHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine){
        setName("PlayerChoiceHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      RequestInputMessage req_input_msg("CLI", msg.getBody());
      message_sender_->sendMessage(req_input_msg);
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};
