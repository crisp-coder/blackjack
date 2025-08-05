#pragma once

#include "message.h"

class ChangeWagerMessage : public Message{
  public:
    ChangeWagerMessage(std::string recipient, std::string body){
      setName("ChangeWagerMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
