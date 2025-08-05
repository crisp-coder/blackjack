#pragma once

#include "message.h"
#include "message_handler.h"

#include "player/bank.h"
#include "player/wager_control.h"

#include "player/messages/to_game/hit_message.h"
#include "player/messages/to_game/stand_message.h"
#include "player/messages/to_game/double_down_message.h"
#include "player/messages/to_game/split_message.h"
#include "player/messages/to_game/surrender_message.h"

#include "player/messages/to_interface/request_input_message.h"
#include "player/messages/to_interface/insufficient_funds_message.h"

class InputMessageHandler : public MessageHandler{
  public:
    InputMessageHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank,
        std::shared_ptr<WagerControl> wager_control){
        setName("InputMessageHandler");
        message_sender_ = sender;
        state_machine_ = state_machine;
        bank_ = bank;
        wager_control_ = wager_control;
    }

    void handle(Message msg){
      std::string input = msg.getBody();
      if(input == "Hit"){
        HitMessage hit_msg("Game", "");
        message_sender_->sendMessage(hit_msg);
      }
      else if(input == "Stand"){
        StandMessage stand_msg("Game", "");
        message_sender_->sendMessage(stand_msg);
      }
      else if(input == "DoubleDown"){
        if(bank_->getBalance() >= wager_control_->getWager()){
          int wager = wager_control_->getWager();
          bank_->withdraw(wager);
          DoubleDownMessage 
            double_down_msg("Game", std::to_string(wager));
          message_sender_->sendMessage(double_down_msg);
        }
        else{
          InsufficientFundsMessage 
            insufficient_funds_msg("CLI",
                "Not enough cash to Double Down.");
          message_sender_->sendMessage(insufficient_funds_msg);

          RequestInputMessage request_input_msg("CLI", "");
          message_sender_->sendMessage(request_input_msg);
        }
      }
      else if(input == "Split"){
        if(bank_->getBalance() >= wager_control_->getWager()){
          int wager = wager_control_->getWager();
          bank_->withdraw(wager);
          SplitMessage split_msg("Game", std::to_string(wager));
          message_sender_->sendMessage(split_msg);
        }
        else{
          InsufficientFundsMessage 
            insufficient_funds_msg("CLI", "Not enough cash to Split.");
          message_sender_->sendMessage(insufficient_funds_msg);

          RequestInputMessage request_input_msg("CLI", "");
          message_sender_->sendMessage(request_input_msg);
        }
      }
      else if(input == "Surrender"){
        SurrenderMessage surrender_msg("Game", "");
        message_sender_->sendMessage(surrender_msg);
      }
      else{
        logger.LOG(bjlogger::ERROR, "Player::InputMessageHandler: bad message received.");
        RequestInputMessage request_input_msg("CLI", "");
        message_sender_->sendMessage(request_input_msg);
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
    std::shared_ptr<WagerControl> wager_control_;
};
