#pragma once

#include "message.h"

class HitMessage : public Message{
  public:
    HitMessage(std::string recipient, std::string body){
      setName("HitMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


