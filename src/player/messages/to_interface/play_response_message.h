#pragma once

#include "message.h"

class PlayResponseMessage : public Message{
  public:
    PlayResponseMessage(std::string recipient, std::string body){
      setName("PlayResponseMessage");
      setRecipient(recipient);
      setBody(body);
    }
};


