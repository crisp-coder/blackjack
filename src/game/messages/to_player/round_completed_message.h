#pragma once

#include "message.h"

class RoundCompletedMessage : public Message{
  public:
    RoundCompletedMessage(std::string recipient, std::string body){
      setName("RoundCompletedMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
