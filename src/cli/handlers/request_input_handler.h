#pragma once

#include <iostream>
#include "message_handler.h"
#include "message.h"
#include "cli/messages/to_player/input_message.h"
#include "utils.h"

class RequestInputHandler: public MessageHandler{
  public:
    RequestInputHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine){
      setName("RequestInputHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
    }

    void handle(Message msg){
      std::vector<std::string> options;
      std::stringstream ss;
      ss << msg.getBody();
      std::string opt = "";
      while(std::getline(ss, opt)){
        opt.erase(std::remove(opt.begin(), opt.end(), '\n'), opt.cend());
        options.push_back(opt);
      }

      while(true){
        std::cout << "Select: ";
        for(auto option : options){
          std::cout << "<" << option << "> ";
        }
        std::cout << std::endl;

        std::string input = "";
        Utils::receiveInput(input);
        if(input == "hit"){
          InputMessage input_msg("Player", "Hit");
          message_sender_->sendMessage(input_msg);
          break;
        }
        else if(input == "stand"){
          InputMessage input_msg("Player", "Stand");
          message_sender_->sendMessage(input_msg);
          break;
        }
        else if(input == "double down"){
          InputMessage input_msg("Player", "DoubleDown");
          message_sender_->sendMessage(input_msg);
          break;
        }
        else if(input == "split"){
          InputMessage input_msg("Player", "Split");
          message_sender_->sendMessage(input_msg);
          break;
        }
        else if(input == "surrender"){
          InputMessage input_msg("Player", "Surrender");
          message_sender_->sendMessage(input_msg);
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

