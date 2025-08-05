#pragma once

#include "message.h"
#include "message_handler.h"
#include "game/messages/to_player/wager_response_message.h"
#include "utils.h"

#include "bjlogger.h"

class WagerHandler : public MessageHandler{
  public:
    WagerHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Table> table){
      setName("WagerHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      table_ = table;
      min_wager_ = 25;
      max_wager_ = 1000;
    }

    void handle(Message msg){
      state_machine_->transition("WagerState");
      int wager_amount = 0;
      if(Utils::isInteger(msg.getBody())){
        logger.LOG(bjlogger::INFO, "Game::WagerHandler: accepted wager."); 
        wager_amount = std::stoi(msg.getBody());
        if(wager_amount < min_wager_ || wager_amount > max_wager_){
          WagerResponseMessage wager_reponse_msg("Player", "Rejected");
          message_sender_->sendMessage(wager_reponse_msg);
          state_machine_->transition("GameStartState");
        }
        else{
          WagerResponseMessage wager_response_msg("Player", "Accepted");
          message_sender_->sendMessage(wager_response_msg);
          table_->setPlayerWager(wager_amount);
          state_machine_->transition("DealState");
        }
      }
      else{
        logger.LOG(bjlogger::ERROR, "Game::WagerHandler: Error, rejected wager."); 
        WagerResponseMessage wager_reponse_msg("Player", "Rejected");
        message_sender_->sendMessage(wager_reponse_msg);
        state_machine_->transition("GameStartState");
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Table> table_;
    int min_wager_;
    int max_wager_;
};


