#pragma once

#include <string>
#include "message.h"

class PlayerBlackjackMessage : public Message{
  public:
    PlayerBlackjackMessage(std::string recipient, std::string body){
      setName("PlayerBlackjackMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
