#pragma once

#include <iostream>

#include "message.h"
#include "message_handler.h"
#include "player/messages/to_interface/display_hand_result_message.h"

class PlayerBustHandler : public MessageHandler{
  public:
    PlayerBustHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank){
        setName("PlayerBustHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      bank_ = bank;
    }

    void handle(Message msg){
      std::string display_message = "Player Bust";
      std::string balance = std::to_string(bank_->getBalance());
      display_message = display_message + "\nBalance is " + balance + "\n";

      DisplayHandResultMessage display_hand_result_msg("CLI", 
          display_message);

      message_sender_->sendMessage(display_hand_result_msg);
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
};
