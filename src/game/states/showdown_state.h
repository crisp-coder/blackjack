#pragma once

#include "state.h"
#include "message.h"

#include "game/messages/to_player/player_blackjack_message.h"
#include "game/messages/to_player/player_bust_message.h"
#include "game/messages/to_player/player_lose_message.h"
#include "game/messages/to_player/player_win_message.h"
#include "game/messages/to_player/player_push_message.h"
#include "game/messages/to_player/player_surrendered_message.h"

#include "game/messages/to_player/round_completed_message.h"

class ShowdownState : public State{
  public:
    ShowdownState(std::shared_ptr<MessageSender> message_sender,
                   std::shared_ptr<StateMachine> state_machine,
                   std::shared_ptr<Table> table){
      setName("ShowdownState");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    bool accept(Message msg){
      return false;
    }

    void onEntry(){
      table_->resetIndex();
      do{
        if(table_->checkPlayerSurrendered()){
          int wager = table_->getPlayerWager();
          int surrender_payout = (wager/2);
          PlayerSurrenderedMessage player_surrender_msg("Player", std::to_string(surrender_payout));
          message_sender_->sendMessage(player_surrender_msg);
        }
        else if(table_->checkPlayerNatural() && !table_->checkDealerNatural()){
          int wager = table_->getPlayerWager();
          int blackjack_payout = wager + (wager * 3)/2;
          PlayerBlackjackMessage player_blackjack_msg("Player", std::to_string(blackjack_payout));
          message_sender_->sendMessage(player_blackjack_msg);
        }
        else if(table_->checkPlayerWin()){
          int wager = table_->getPlayerWager();
          int payout = wager+wager;
          PlayerWinMessage player_win_msg("Player", std::to_string(payout));
          message_sender_->sendMessage(player_win_msg);
        } 
        else if(table_->checkPlayerPush() || (table_->checkPlayerNatural() && table_->checkDealerNatural())){
          int wager = table_->getPlayerWager();
          int payout = wager;
          PlayerPushMessage player_push_msg("Player", std::to_string(payout));
          message_sender_->sendMessage(player_push_msg);
        }
        else if(table_->checkPlayerBust()){
          PlayerBustMessage player_bust_msg("Player", "0");
          message_sender_->sendMessage(player_bust_msg);
        }
        else{
          PlayerLoseMessage player_lose_msg("Player", "0");
          message_sender_->sendMessage(player_lose_msg);
        }
      } while(table_->nextHand());

      RoundCompletedMessage round_completed_msg("Player", "");
      message_sender_->sendMessage(round_completed_msg);
      state_machine_->transition("GameStartState");
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Table> table_;
};

