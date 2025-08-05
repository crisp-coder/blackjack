#pragma once

#include <string>
#include "message.h"

class HandResultMessage : public Message{
  public:
    HandResultMessage(std::string recipient, std::string body){
      setName("HandResultMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
