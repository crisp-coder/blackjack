#pragma once

#include <string>
#include "message.h"

class PlayerChoiceMessage : public Message{
  public:
    PlayerChoiceMessage(std::string recipient, std::string body){
      setName("PlayerChoiceMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
