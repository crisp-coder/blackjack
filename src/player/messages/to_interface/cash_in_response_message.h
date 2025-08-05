#pragma once

#include <string>
#include "message.h"

class CashInResponseMessage : public Message{
  public:
    CashInResponseMessage(std::string recipient, std::string body){
      setName("CashInResponseMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


