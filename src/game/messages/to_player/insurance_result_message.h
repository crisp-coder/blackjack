#pragma once

#include "message.h"

class InsuranceResultMessage : public Message{
  public:
    InsuranceResultMessage(std::string recipient, std::string body){
      setName("InsuranceResultMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
