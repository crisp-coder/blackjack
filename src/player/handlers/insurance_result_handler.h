#pragma once

#include <iostream>

#include "message.h"
#include "message_handler.h"
#include "player/messages/to_interface/display_insurance_result_message.h"

class InsuranceResultHandler : public MessageHandler{
  public:
    InsuranceResultHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank,
        std::shared_ptr<WagerControl> wager_control){
        setName("InsuranceResultHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      bank_ = bank;
      wager_control_ = wager_control;
    }

    void handle(Message msg){
      if(msg.getBody() == "Win"){
        bank_->add(wager_control_->getWager());
        DisplayInsuranceResultMessage 
          disp_ins_result_msg("CLI", "Win");
        message_sender_->sendMessage(disp_ins_result_msg);
      }
      else if(msg.getBody() == "Lose"){
        bank_->withdraw(wager_control_->getWager()/2);
        DisplayInsuranceResultMessage 
          disp_ins_result_msg("CLI", "Lose");
        message_sender_->sendMessage(disp_ins_result_msg);
      }
      else{
        logger.LOG(bjlogger::ERROR, "Player::InsuranceResultHandler: received bad message.");
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
    std::shared_ptr<WagerControl> wager_control_;
};
