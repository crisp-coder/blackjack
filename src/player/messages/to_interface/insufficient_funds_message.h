#pragma once

#include <string>
#include "message.h"

class InsufficientFundsMessage : public Message{
  public:
    InsufficientFundsMessage(std::string recipient, std::string body){
      setName("InsufficientFundsMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


