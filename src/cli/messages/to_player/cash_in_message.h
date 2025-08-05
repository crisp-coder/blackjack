#pragma once

#include <string>
#include "message.h"

class CashInMessage : public Message{
  public:
    CashInMessage(std::string recipient, std::string body){
      setName("CashInMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
