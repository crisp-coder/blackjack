#pragma once

#include "message.h"
#include "message_sender.h"
#include "message_handler.h"
#include "state_machine.h"

class PlayResponseHandler: public MessageHandler{
  public:
    PlayResponseHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine){
      setName("PlayResponseHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      if(msg.getBody() == "Accepted"){
        state_machine_->transition("PlayingHandState");
      }
      else if(msg.getBody() == "Rejected"){
        std::cout << "Play hand rejected." << std::endl;
        state_machine_->transition("CLIStartState");
      }
      else{
        logger.LOG(bjlogger::ERROR, "CLI::PlayResponseHandler: received bad message.");
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};

