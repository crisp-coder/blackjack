#pragma once

#include <string>
#include "message.h"

class CheckBalanceMessage : public Message{
  public:
    CheckBalanceMessage(std::string recipient, std::string body){
      setName("CheckBalanceMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
