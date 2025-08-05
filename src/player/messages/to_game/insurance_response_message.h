#pragma once

#include "message.h"

class InsuranceResponseMessage : public Message{
  public:
    InsuranceResponseMessage(std::string recipient, std::string body){
      setName("InsuranceResponseMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


