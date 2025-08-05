#pragma once

#include "message.h"

class NullMessage : public Message{
  public:
    NullMessage(std::string recipient, std::string body){
      setName("NullMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
