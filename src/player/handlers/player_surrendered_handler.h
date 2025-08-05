#pragma once

#include <iostream>

#include "message.h"
#include "message_handler.h"
#include "player/messages/to_interface/display_hand_result_message.h"

#include "utils/utils.h"

class PlayerSurrenderedHandler : public MessageHandler{
  public:
    PlayerSurrenderedHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank){
        setName("PlayerSurrenderedHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      bank_ = bank;
    }

    void handle(Message msg){
      int winnings = 0;
      if(Utils::isInteger(msg.getBody())){
        winnings = std::stoi(msg.getBody());
      }
      else{
        logger.LOG(bjlogger::ERROR, "Player::PlayerSurrenderedHandler: bad integer.");
        winnings = 0;
      }
      bank_->add(winnings);
      std::string balance = std::to_string(bank_->getBalance());
      std::string display_message = "Player Surrendered\n";
      display_message += "Balance is " + balance + "\n";

      DisplayHandResultMessage display_hand_result_msg("CLI", 
          display_message);
      message_sender_->sendMessage(display_hand_result_msg);
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
};
