#pragma once

#include "message.h"

class DisplayTableMessage : public Message{

  public:
    DisplayTableMessage(std::string recipient, std::string body){
      setName("DisplayTableMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
