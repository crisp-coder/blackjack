#pragma once

#include <string>
#include "message.h"

class ChangeWagerResponseMessage : public Message{
  public:
    ChangeWagerResponseMessage(std::string recipient, std::string body){
      setName("ChangeWagerResponseMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


