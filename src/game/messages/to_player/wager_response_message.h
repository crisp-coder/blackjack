#pragma once

#include "message.h"

class WagerResponseMessage : public Message{
  public:
    WagerResponseMessage(std::string recipient, std::string body){
      setName("WagerResponseMessage");
      setRecipient(recipient);
      setBody(body);
    }

};
