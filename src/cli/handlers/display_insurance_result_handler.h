#pragma once

#include <string>
#include <iostream>
#include "message_handler.h"
#include "message.h"
#include "utils.h"

class DisplayInsuranceResultHandler: public MessageHandler{
  public:
    DisplayInsuranceResultHandler(std::shared_ptr<MessageSender> sender,
      std::shared_ptr<StateMachine> state_machine){
      setName("DisplayInsuranceResultHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      if(msg.getBody() == "Win"){
        std::cout << "Insurance Bet Wins!" << std::endl;
      }
      else if(msg.getBody() == "Lose"){
        std::cout << "Insurance Bet Loses." << std::endl;
      }
      else{
        logger.LOG(bjlogger::ERROR, "CLI::DisplayInsuranceResultHandler: received bad message.");
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};

