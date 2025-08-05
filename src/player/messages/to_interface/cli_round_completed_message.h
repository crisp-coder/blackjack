#pragma once

#include <string>
#include "message.h"

class CLIRoundCompletedMessage : public Message{
  public:
    CLIRoundCompletedMessage(std::string recipient, std::string body){
      setName("CLIRoundCompletedMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


