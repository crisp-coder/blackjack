#pragma once

#include <string>
#include "message.h"

class DisplayInsuranceResultMessage : public Message{
  public:
    DisplayInsuranceResultMessage(std::string recipient, std::string body){
      setName("DisplayInsuranceResultMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


