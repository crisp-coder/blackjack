#pragma once

#include "message_handler.h"
#include "message.h"

#include "cli/messages/to_player/play_hand_message.h"

class PlayHandHandler: public MessageHandler{
  public:
    PlayHandHandler(std::shared_ptr<MessageSender> sender,
      std::shared_ptr<StateMachine> state_machine){
      setName("PlayHandHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      PlayHandMessage play_hand_msg("Player", "");
      message_sender_->sendMessage(play_hand_msg);
      state_machine_->transition("WaitState");
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};

