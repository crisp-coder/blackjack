#pragma once

#include "state.h"
#include "message.h"
#include "game/messages/to_player/player_choice_message.h"

class PlayerTurnState : public State{
  public:
    PlayerTurnState(std::shared_ptr<MessageSender> message_sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Table> table){
      setName("PlayerTurnState");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
      table_ = table;
    }

    bool accept(Message msg){
      std::string name = msg.getName();
      return name == "RestartMessage" ||
        name == "QuitMessage" || 
        name == "HitMessage" ||
        name == "DoubleDownMessage" ||
        name == "SplitMessage" ||
        name == "SurrenderMessage" ||
        name == "StandMessage";
    }

    void onEntry(){
      if(table_->checkPlayerHas21()){
        if(table_->nextHand()){
          state_machine_->transition("PlayerTurnState");
        }
        else{
          state_machine_->transition("DealerTurnState");
        }
      }
      else{
        std::string options = "";
        if(table_->playerCanHit()){
          options += "Hit\n";
        }
        if(table_->playerCanStand()){
          options += "Stand\n";
        }
        if(table_->playerCanSplit()){
          options += "Split\n";
        }
        if(table_->playerCanSurrender()){
          options += "Surrender\n";
        }
        if(table_->playerCanDoubleDown()){
          options += "Double Down\n";
        }
        if(options == ""){
          state_machine_->transition("DealerTurnState");
        }
        PlayerChoiceMessage player_choice_msg("Player", options);
        message_sender_->sendMessage(player_choice_msg);
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Table> table_;
};

