#pragma once

#include "message.h"
#include "message_handler.h"

#include "player/bank.h"
#include "player/wager_control.h"

#include "player/messages/to_interface/insufficient_funds_message.h"
#include "player/messages/to_interface/change_wager_response_message.h"

class ChangeWagerHandler : public MessageHandler{
  public:
    ChangeWagerHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank,
        std::shared_ptr<WagerControl> wager_control){
      setName("ChangeWagerHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      bank_ = bank;
      wager_control_ = wager_control;
    }

    void handle(Message msg){
      if(Utils::isInteger(msg.getBody())){
        int wager = std::stoi(msg.getBody());
        if(bank_->getBalance() >= wager){
          wager_control_->setWager(wager);
          ChangeWagerResponseMessage change_wager_resp("CLI", "Accepted");
          message_sender_->sendMessage(change_wager_resp);
        }
        else{
          InsufficientFundsMessage insufficient_funds_msg("CLI", "Not enough cash");
          message_sender_->sendMessage(insufficient_funds_msg);

          ChangeWagerResponseMessage change_wager_resp("CLI", "Rejected");
          message_sender_->sendMessage(change_wager_resp);
        }
      }
      else{
        logger.LOG(bjlogger::ERROR, "Player::ChangeWagerHandler: bad integer.");
        ChangeWagerResponseMessage change_wager_resp("CLI", "Rejected");
        message_sender_->sendMessage(change_wager_resp);
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
    std::shared_ptr<WagerControl> wager_control_;
};
