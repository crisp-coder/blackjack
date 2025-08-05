#pragma once

#include <memory>
#include "message.h"
#include "message_queue.h"
#include "message_sender.h"
#include "message_receiver.h"
#include "state_machine.h"
#include "dispatcher.h"

class MessageSender;

class Module : public MessageReceiver{ 
  public:
    Module(){
    }

    void setMessageSender(std::shared_ptr<MessageSender>& msg_sender){
      msg_sender_ = msg_sender;
    }

    void setStateMachine(std::shared_ptr<StateMachine>& state_machine){
      state_machine_ = state_machine;
    }

    void setDispatcher(std::shared_ptr<Dispatcher> dispatcher){
      dispatcher_ = dispatcher;
    }

    void sendMessage(Message msg){
      msg_sender_->sendMessage(msg);
    }

    virtual void receiveMessage(Message msg){
      msg_queue_.push(msg);
    }

    void processMessage(){
      if(!msg_queue_.empty()){
        dispatcher_->dispatch(msg_queue_.getMessage());
      }
    }

    virtual std::string getName(){
      return name_;
    }

    void setName(std::string name){
      name_ = name;
    }

    virtual bool isQuitState(){
      return false;
    }
  protected:
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<MessageSender> msg_sender_;
  private:
    std::string name_;
    std::shared_ptr<Dispatcher> dispatcher_;
    MessageQueue msg_queue_;
};
