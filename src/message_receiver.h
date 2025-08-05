#pragma once

class MessageReceiver{
  public:
    virtual void receiveMessage(Message msg) = 0;
    virtual std::string getName() = 0;
};
