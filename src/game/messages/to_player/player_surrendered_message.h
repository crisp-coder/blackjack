#pragma once

#include <string>
#include "message.h"

class PlayerSurrenderedMessage : public Message{
  public:
    PlayerSurrenderedMessage(std::string recipient, std::string body){
      setName("PlayerSurrenderedMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
