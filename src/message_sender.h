#pragma once

#include <string>
#include <map>
#include <memory>
#include "message.h"
#include "message_receiver.h"
#include "bjlogger.h"

class MessageSender{
  public:
    MessageSender(){
    }

    void registerReceiver(std::shared_ptr<MessageReceiver> m){
      registry_[m->getName()] = m;
    }

    void sendMessage(Message msg){
      logger.LOG(
        bjlogger::INFO, 
        "MessageSender::Routing message " + msg.getName() + " to " + msg.getRecipient()
      );

      logger.LOG(bjlogger::INFO, msg.getBody());
      registry_[msg.getRecipient()]->receiveMessage(msg);
    }

  private:
    std::map<std::string, std::shared_ptr<MessageReceiver>> registry_;
};
