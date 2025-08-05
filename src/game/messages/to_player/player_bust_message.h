#pragma once

#include <string>
#include "message.h"

class PlayerBustMessage : public Message{
  public:
    PlayerBustMessage(std::string recipient, std::string body){
      setName("PlayerBustMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
