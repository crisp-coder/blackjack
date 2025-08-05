#pragma once

#include "message.h"
#include "message_handler.h"
#include "player/messages/to_interface/play_response_message.h"

class WagerResponseHandler : public MessageHandler{
  public:
    WagerResponseHandler(std::shared_ptr<MessageSender> message_sender,
        std::shared_ptr<StateMachine> state_machine){
      setName("WagerResponseHandler");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      if(msg.getBody() == "Accepted"){
        PlayResponseMessage play_response_msg("CLI", "Accepted");
        message_sender_->sendMessage(play_response_msg);
        state_machine_->transition("PlayState");
      }
      else if(msg.getBody() == "Rejected"){
        PlayResponseMessage play_response_msg("CLI", "Rejected");
        message_sender_->sendMessage(play_response_msg);
        state_machine_->transition("PlayerStartState");
      }
      else{
        logger.LOG(bjlogger::ERROR, "WagerResponseHandler:: bad message received");
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};
