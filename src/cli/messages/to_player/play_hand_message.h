#pragma once

#include <string>
#include "message.h"

class PlayHandMessage : public Message{
  public:
    PlayHandMessage(std::string recipient, std::string body){
      setName("PlayHandMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
