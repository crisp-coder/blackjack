#pragma once

#include "state.h"
#include "message.h"
#include "message_sender.h"
#include "game/messages/to_player/insurance_offer_message.h"

class InsuranceState : public State{
  public:
    InsuranceState(std::shared_ptr<MessageSender> message_sender,
              std::shared_ptr<StateMachine> state_machine,
              std::shared_ptr<Table> table){
      state_machine_ = state_machine;
      message_sender_ = message_sender;
      table_ = table;
      setName("InsuranceState");
    }

    bool accept(Message msg){
      std::string name = msg.getName();
      return name == "InsuranceResponseMessage" || 
             name == "RestartMessage" ||
             name == "QuitMessage";
    }

    void onEntry(){
      InsuranceOfferMessage insurance_offer_msg("Player", "");
      message_sender_->sendMessage(insurance_offer_msg);
    }

  private:
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<Table> table_;
};


