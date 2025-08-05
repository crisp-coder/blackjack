#pragma once

#include <string>
#include "message.h"

class PlayerLoseMessage : public Message{
  public:
    PlayerLoseMessage(std::string recipient, std::string body){
      setName("PlayerLoseMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
