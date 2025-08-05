#pragma once

#include "message.h"
#include "message_handler.h"

#include "player/messages/to_interface/cash_in_response_message.h"

#include "utils/utils.h"

class CashInHandler : public MessageHandler{
  public:
    CashInHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank){
        setName("CashInHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      bank_ = bank;
    }

    void handle(Message msg){
      if(Utils::isInteger(msg.getBody())){
        bank_->add(std::stoi(msg.getBody()));
        CashInResponseMessage cash_in_response_msg("CLI", "Accepted");
        message_sender_->sendMessage(cash_in_response_msg);
      }
      else{
        logger.LOG(bjlogger::ERROR, "Player::CashInHandler: bad integer.");
        CashInResponseMessage cash_in_response_msg("CLI", "Rejected");
        message_sender_->sendMessage(cash_in_response_msg);
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
};
