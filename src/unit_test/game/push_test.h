#pragma once

#include "message_sender.h"
#include "test.h"
#include "game.h"
#include "push_test_deck.h"
#include "player/messages/to_game/wager_message.h"

class PushTest : public Test{
  public:
    PushTest(){
      setName("PushTest");

      // Test 1
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));

      addMessage(std::make_shared<StandMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerPushMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));

      // Test 2
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));
      
      addMessage(std::make_shared<HitMessage>("Game", "25"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));
      
      addMessage(std::make_shared<StandMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerPushMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));

      // Test 3
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));

      addMessage(std::make_shared<HitMessage>("Game", "25"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerPushMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));

      // Test 4
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));

      addResponseMessage(std::make_shared<InsuranceOfferMessage>("Player", ""));
      addMessage(std::make_shared<InsuranceResponseMessage>("Game", "Rejected"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerPushMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));
    }
    
    void setup(std::shared_ptr<MessageSender> msg_sender){
      game_ = std::make_shared<Game>(msg_sender);
      // Must register new game instance on setup.
      msg_sender->registerReceiver(game_);
      deck_ = std::make_shared<PushTestDeck>();
      game_->getTable()->setDeck(deck_);
      setTarget(game_);
    }

  private:
    std::shared_ptr<Deck> deck_;
    std::shared_ptr<Game> game_;
    std::shared_ptr<MessageSender> msg_sender_;
};


