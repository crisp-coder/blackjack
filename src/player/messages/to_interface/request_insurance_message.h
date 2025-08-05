#pragma once

#include "message.h"

class RequestInsuranceMessage : public Message{
  public:
    RequestInsuranceMessage(std::string recipient, std::string body){
      setName("RequestInsuranceMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


