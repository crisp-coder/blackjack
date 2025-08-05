#pragma once

#include <string>
#include "message.h"

class TableDataMessage : public Message{
  public:
    TableDataMessage(std::string recipient, std::string body){
      setName("TableDataMessage");
      setRecipient(recipient);
      setBody(body);
    }
};
