#pragma once

#include "message.h"
#include "message_handler.h"
#include "player/messages/to_interface/request_insurance_message.h"

class InsuranceOfferHandler : public MessageHandler{
  public:
    InsuranceOfferHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank){
        setName("InsuranceOfferHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      bank_ = bank;
    }

    void handle(Message msg){
      RequestInsuranceMessage request_insurance_msg("CLI", "");
      message_sender_->sendMessage(request_insurance_msg);
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
};
