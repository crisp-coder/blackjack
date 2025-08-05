#pragma once

#include <string>
#include "message.h"

class PlayerWinMessage : public Message{
  public:
    PlayerWinMessage(std::string recipient, std::string body){
      setName("PlayerWinMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
