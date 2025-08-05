#pragma once

#include <string>
#include "message.h"

class SurrenderMessage : public Message{
  public:
    SurrenderMessage(std::string recipient, std::string body){
      setName("SurrenderMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
