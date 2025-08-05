#pragma once

#include <string>
#include "message.h"

class RequestInputMessage : public Message{
  public:
    RequestInputMessage(std::string recipient, std::string body){
      setName("RequestInputMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


