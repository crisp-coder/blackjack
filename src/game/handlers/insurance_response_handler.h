#pragma once

#include <string>
#include <iostream>
#include "message_handler.h"
#include "message.h"
#include "game/messages/to_player/table_data_message.h"
#include "game/messages/to_player/insurance_result_message.h"
#include "utils.h"

class InsuranceResponseHandler : public MessageHandler{
  public:
    InsuranceResponseHandler(std::shared_ptr<MessageSender> message_sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Table> table){
      setName("InsuranceResponseHandler");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    void handle(Message msg){
      if(msg.getBody() == "Accepted"){
        if(table_->checkDealerNatural()){
          InsuranceResultMessage insurance_result_msg("Player", "Win");
          message_sender_->sendMessage(insurance_result_msg);
          table_->setDealerHoleCardFaceUp();
          TableDataMessage table_data_msg("Player", table_->encode());
          message_sender_->sendMessage(table_data_msg);
          state_machine_->transition("ShowdownState");
        }
        else{
          InsuranceResultMessage insurance_result_msg("Player", "Lose");
          message_sender_->sendMessage(insurance_result_msg);
          state_machine_->transition("PlayerTurnState");
        }
      }
      else if(msg.getBody() == "Rejected"){
        if(table_->checkDealerNatural()){
          TableDataMessage table_data_msg("Player", table_->encode());
          message_sender_->sendMessage(table_data_msg);
          state_machine_->transition("ShowdownState");
        }
        else{
          state_machine_->transition("PlayerTurnState");        
        }
      }
      else{
        logger.LOG(bjlogger::ERROR, "Game::InsuranceResponseHandler: bad message received.");
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Table> table_;
};

