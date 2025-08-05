#pragma once

#include "message.h"

class InsuranceOfferMessage : public Message{
  public:
    InsuranceOfferMessage(std::string recipient, std::string body){
      setName("InsuranceOfferMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
