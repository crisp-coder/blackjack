#pragma once

#include <string>
#include "message.h"

class InsuranceMessage : public Message{
  public:
    InsuranceMessage(std::string recipient, std::string body){
      setName("InsuranceMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
