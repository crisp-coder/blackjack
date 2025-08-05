#pragma once

#include <string>
#include "message.h"

class DisplayBalanceMessage : public Message{
  public:
    DisplayBalanceMessage(std::string recipient, std::string body){
      setName("DisplayBalanceMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


