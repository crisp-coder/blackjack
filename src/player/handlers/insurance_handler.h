#pragma once

#include "message.h"
#include "message_handler.h"

#include "player/bank.h"
#include "player/wager_control.h"

#include "player/messages/to_game/insurance_response_message.h"
#include "player/messages/to_interface/request_insurance_message.h"
#include "player/messages/to_interface/insufficient_funds_message.h"

class InsuranceHandler : public MessageHandler{
  public:
    InsuranceHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank,
        std::shared_ptr<WagerControl> wager_control){
      setName("InsuranceHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      bank_ = bank;
      wager_control_ = wager_control;
    }

    void handle(Message msg){
      std::string input = msg.getBody();
      if(bank_->getBalance() >= wager_control_->getWager()/2){
        if(input == "Accepted"){
          InsuranceResponseMessage insurance_resp_msg("Game", "Accepted");
          message_sender_->sendMessage(insurance_resp_msg);
        }
        else if(input == "Rejected"){
          InsuranceResponseMessage insurance_resp_msg("Game", "Rejected");
          message_sender_->sendMessage(insurance_resp_msg);
        }
        else{
          logger.LOG(bjlogger::ERROR, "Player::InsuranceHandler: received bad message.");
          RequestInsuranceMessage request_insurance_msg("CLI", "");
          message_sender_->sendMessage(request_insurance_msg);
        }
      }
      else{
        InsufficientFundsMessage 
          insufficient_funds_msg("CLI", "Insufficient funds to place insurance bet.");
        message_sender_->sendMessage(insufficient_funds_msg);

        InsuranceResponseMessage insurance_resp_msg("Game", "Rejected");
        message_sender_->sendMessage(insurance_resp_msg);
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
    std::shared_ptr<WagerControl> wager_control_;
};
