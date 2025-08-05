#pragma once

#include "message.h"
#include "message_handler.h"
#include "player/messages/to_interface/display_balance_message.h"

class CheckBalanceHandler : public MessageHandler{
  public:
    CheckBalanceHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank){
        setName("CheckBalanceHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      bank_ = bank;
    }

    void handle(Message msg){
      std::string balance = std::to_string(bank_->getBalance());
      DisplayBalanceMessage balance_msg("CLI", balance);
      message_sender_->sendMessage(balance_msg);
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
};
