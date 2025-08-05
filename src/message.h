#pragma once

#include <string>

class Message{
  public:
    Message(){
      name_ = "message";
      recipient_ = "none";
    }
    
    /**
     * Constructor that takes a recipient and body so the message can be passed
     * to its intended recipient with accompanying data.
     * */
    Message(std::string& recipient, std::string& body){
      name_ = "message";
      recipient_ = recipient;
      body_ = body;
    }

    virtual ~Message(){
    }
    
    virtual void setBody(std::string str){
      body_ = str;
    }

    virtual std::string getBody(){
      return body_;
    }
 
    /**
     * This method allows subclasses to override the default message name.
     * */
    virtual void setName(std::string name){
      name_ = name;
    }
    
    virtual std::string getName(){
      return name_;
    }

    virtual void setRecipient(std::string recipient){
      recipient_ = recipient;
    }

    virtual std::string getRecipient(){
      return recipient_;
    }

    private:
      std::string body_;
      std::string name_;
      std::string recipient_;
};
