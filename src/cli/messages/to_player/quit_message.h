#pragma once

#include <string>
#include "message.h"

class QuitMessage : public Message{
  public:
    QuitMessage(std::string recipient, std::string body){
      setName("QuitMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
