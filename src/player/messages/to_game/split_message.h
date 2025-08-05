#pragma once

#include <string>
#include "message.h"

class SplitMessage : public Message{
  public:
    SplitMessage(std::string recipient, std::string body){
      setName("SplitMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


