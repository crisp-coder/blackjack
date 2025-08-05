#pragma once

#include "message_sender.h"
#include "test.h"
#include "game.h"
#include "test_deck.h"
#include "player/messages/to_game/wager_message.h"
#include "game/messages/to_player/wager_response_message.h"

class MaxWagerTest : public Test{
  public:
    MaxWagerTest(){
      setName("MaxWagerTest");
      addMessage(std::make_shared<WagerMessage>("Game", "1000"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));
    }
    
    void setup(std::shared_ptr<MessageSender> msg_sender){
      game_ = std::make_shared<Game>(msg_sender);
      // Must register new game instance on setup.
      msg_sender->registerReceiver(game_);
      deck_ = std::make_shared<TestDeck>();
      game_->getTable()->setDeck(deck_);
      setTarget(game_);
    }

  private:
    std::shared_ptr<Deck> deck_;
    std::shared_ptr<Game> game_;
    std::shared_ptr<MessageSender> msg_sender_;
};

