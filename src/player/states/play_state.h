#pragma once

#include "state.h"
#include "message.h"

class PlayState : public State{
  public:
    PlayState(){
      setName("PlayState");
    }

    bool accept(Message msg){
      std::string name = msg.getName();
      return name == "QuitMessage" ||
        name == "RestartMessage" ||
        name == "RoundCompletedMessage" ||
        name == "PlayerWinMessage" ||
        name == "PlayerLoseMessage" ||
        name == "PlayerBustMessage" ||
        name == "PlayerPushMessage" ||
        name == "PlayerSurrenderedMessage" ||
        name == "PlayerBlackjackMessage" ||
        name == "PlayerChoiceMessage" ||
        name == "InsuranceOfferMessage" ||
        name == "InsuranceMessage" ||
        name == "InsuranceResultMessage" ||
        name == "InputMessage" || 
        name == "TableDataMessage"; 
    }

    void onEntry(){
    }
};


