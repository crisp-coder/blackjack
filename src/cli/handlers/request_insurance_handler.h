#pragma once

#include <iostream>
#include "message.h"
#include "message_handler.h"
#include "cli/messages/to_player/insurance_message.h"
#include "utils.h"

class RequestInsuranceHandler: public MessageHandler{
  public:
    RequestInsuranceHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine){
      setName("RequestInsuranceHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      while(true){
        std::cout << "Insurance?: <Yes> <No>" << std::endl;
        std::string input = "";
        Utils::receiveInput(input);
        if(input == "yes"){
          InsuranceMessage req_ins_resp_msg("Player", "Accepted");
          message_sender_->sendMessage(req_ins_resp_msg);
          break;
        }
        else if(input == "no"){
          InsuranceMessage req_ins_resp_msg("Player", "Rejected");
          message_sender_->sendMessage(req_ins_resp_msg);
          break;
        }
        else{
          std::cout << "Invalid option" << std::endl;
        }
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};

