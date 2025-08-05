#pragma once

#include <string>
#include "message.h"

class InputMessage : public Message{
  public:
    InputMessage(std::string recipient, std::string body){
      setName("InputMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
