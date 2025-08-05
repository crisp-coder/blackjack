#pragma once

#include <string>
#include "message.h"

class RestartMessage : public Message{
  public:
    RestartMessage(std::string recipient, std::string body){
      setName("RestartMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
