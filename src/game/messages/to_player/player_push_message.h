#pragma once

#include <string>
#include "message.h"

class PlayerPushMessage : public Message{
  public:
    PlayerPushMessage(std::string recipient, std::string body){
      setName("PlayerPushMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
