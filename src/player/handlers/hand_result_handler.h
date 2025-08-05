#pragma once

#include <sstream>
#include <iostream>

#include "message.h"
#include "message_handler.h"
#include "player/messages/to_interface/display_hand_result_message.h"

#include "utils/utils.h"

class HandResultHandler : public MessageHandler{
  public:
    HandResultHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank){
        setName("HandResultHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      bank_ = bank;
    }

    void handle(Message msg){
      std::string result = "";
      std::string winnings_str = "";
      int winnings = 0;
      std::stringstream ss;
      ss << msg.getBody();
      std::getline(ss, winnings_str);
      if(Utils::isInteger(winnings_str)){
        winnings = std::stoi(winnings_str);
      }
      else{
        logger.LOG(bjlogger::ERROR, "Player::HandResultHandler: bad integer.");
        winnings = 0;
      }
      std::getline(ss, result);
      ss.clear();
      ss.str("");
      std::string display_message; 

      if(result == "Bust"){
        display_message = "Player Bust";
      }
      else if(result == "Push"){
        bank_->add(winnings);
        ss << "Player Push, returned wager " << winnings;
        display_message = ss.str();
      }
      else if(result == "Blackjack"){
        bank_->add(winnings);
        ss << "Player has Blackjack! Won " << winnings << "!";
        display_message = ss.str();
      }
      else if(result == "Win"){
        bank_->add(winnings);
        ss << "Player Wins! Won " << winnings << "!";
        display_message = ss.str();
      }
      else if(result == "Lose"){
        display_message = "Player Loses";
      }
      else if(result == "Surrendered"){
        bank_->add(winnings);
        display_message = "Player Surrendered";
      }

      ss.clear();
      ss.str("");
      std::string balance = std::to_string(bank_->getBalance());
      ss << display_message << "\n";
      ss << "Balance is " + balance << "\n";
      display_message = ss.str();

      DisplayHandResultMessage display_hand_result_msg("CLI", 
          display_message);
      message_sender_->sendMessage(display_hand_result_msg);
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
};
