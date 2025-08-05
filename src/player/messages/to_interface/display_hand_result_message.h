#pragma once

#include <string>
#include "message.h"

class DisplayHandResultMessage : public Message{

  public:
    DisplayHandResultMessage(std::string recipient, std::string body){
      setName("DisplayHandResultMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
