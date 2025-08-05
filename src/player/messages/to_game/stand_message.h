#pragma once

#include "message.h"

class StandMessage : public Message{
  public:
    StandMessage(std::string recipient, std::string body){
      setName("StandMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


