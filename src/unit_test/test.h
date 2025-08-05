#pragma once

#include <vector>
#include <string>
#include <memory>

#include "message.h"
#include "null_message.h"
#include "message_sender.h"
#include "module.h"

/**
 * A test is a collection of messages and their expected responses.
 * Tests should be run from a test module.
 */
class Test{
  public:
    Test(){
      name_ = "none";
      msg_num_ = 0;
      resp_num_ = 0;
    }

    Test(std::string name, std::shared_ptr<Module> target){
      name_ = name;
      msg_num_ = 0;
      resp_num_ = 0;
      target_ = target;
    }

    /**
     * Set the target module to be tested.
     * The target will receive the messages sent by the test module.
     * The test module will compare response messages from the target
     * to the expected response in the test.
     */
    void setTarget(std::shared_ptr<Module> target){
      target_ = target;
    }

    std::shared_ptr<Module> getTarget(){
      return target_;
    }

    virtual void setup(std::shared_ptr<MessageSender> msg_sender){
    }

    std::string getName(){
      return name_;
    }

    void setName(std::string name){
      name_ = name;
    }

    void addMessage(std::shared_ptr<Message> msg){
      message_sequence_.push_back(*msg);
    }
    
    void addResponseMessage(std::shared_ptr<Message> response_msg){
      response_sequence_.push_back(*response_msg);
    }
    
    std::shared_ptr<Message> getNextMessage(){
      if(msg_num_ < message_sequence_.size()){
        return std::make_shared<Message>(message_sequence_[msg_num_++]);
      }        
      else{
        return std::make_shared<NullMessage>("", "");
      }
    }

    std::shared_ptr<Message> getNextResponse(){
      if(resp_num_ < response_sequence_.size()){
        return std::make_shared<Message>(response_sequence_[resp_num_++]);
      }        
      else{
        return std::make_shared<NullMessage>("", "");
      }
    }

  private:
    std::string name_;
    std::shared_ptr<Module> target_;
    std::vector<Message> message_sequence_;
    std::vector<Message> response_sequence_;
    int msg_num_;
    int resp_num_;
};


