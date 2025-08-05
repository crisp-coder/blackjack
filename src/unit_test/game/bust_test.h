#pragma once

#include "message_sender.h"
#include "test.h"
#include "game.h"
#include "bust_test_deck.h"
#include "player/messages/to_game/wager_message.h"

class BustTest : public Test{
  public:
    BustTest(){
      setName("BustTest");

      // Test 1
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));

      addMessage(std::make_shared<HitMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerBustMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));

      // Test 2
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));

      addMessage(std::make_shared<HitMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerBustMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));
      
      // Test 3
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));

      addMessage(std::make_shared<HitMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));

      addMessage(std::make_shared<HitMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerBustMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));

      // Test 4
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));

      addMessage(std::make_shared<HitMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));

      addMessage(std::make_shared<HitMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerBustMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));
    }
    
    void setup(std::shared_ptr<MessageSender> msg_sender){
      game_ = std::make_shared<Game>(msg_sender);
      // Must register new game instance on setup.
      msg_sender->registerReceiver(game_);
      deck_ = std::make_shared<BustTestDeck>();
      game_->getTable()->setDeck(deck_);
      setTarget(game_);
    }

  private:
    std::shared_ptr<Deck> deck_;
    std::shared_ptr<Game> game_;
    std::shared_ptr<MessageSender> msg_sender_;
};

