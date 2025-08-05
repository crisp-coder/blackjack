#pragma once

#include <string>
#include "message.h"

class WagerMessage : public Message{
  public:
    WagerMessage(std::string recipient, std::string body){
      setName("WagerMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


