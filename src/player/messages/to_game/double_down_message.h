#pragma once

#include <string>
#include "message.h"

class DoubleDownMessage : public Message{
  public:
    DoubleDownMessage(std::string recipient, std::string body){
      setName("DoubleDownMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


