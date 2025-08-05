#pragma once

#include "message.h"
#include "message_handler.h"

#include "player/bank.h"
#include "player/wager_control.h"

#include "player/messages/to_game/wager_message.h"
#include "player/messages/to_interface/play_response_message.h"
#include "player/messages/to_interface/insufficient_funds_message.h"

class PlayHandler : public MessageHandler{
  public:
    PlayHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank,
        std::shared_ptr<WagerControl> wager_control){
      setName("PlayHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      wager_control_ = wager_control;
      bank_ = bank;
    }

    void handle(Message msg){
      int wager_amount = wager_control_->getWager();
      if(bank_->getBalance() > wager_amount){
        bank_->withdraw(wager_amount);
        WagerMessage wager_msg("Game", std::to_string(wager_amount));
        message_sender_->sendMessage(wager_msg);
      }
      else{
        InsufficientFundsMessage 
          insufficient_funds_msg("CLI", "Not enough cash");
        message_sender_->sendMessage(insufficient_funds_msg);

        PlayResponseMessage play_response_msg("CLI", "Rejected");
        message_sender_->sendMessage(play_response_msg);
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<WagerControl> wager_control_;
    std::shared_ptr<Bank> bank_;
};

