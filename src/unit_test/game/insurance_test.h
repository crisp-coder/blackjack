#pragma once

#include "message_sender.h"
#include "test.h"
#include "game.h"
#include "insurance_test_deck.h"

class InsuranceTest : public Test{
  public:
    InsuranceTest(){
      setName("InsuranceTest");

      // Start Hand
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<InsuranceOfferMessage>("Player", ""));
      addMessage(std::make_shared<InsuranceResponseMessage>("Game", "Accepted"));
      // Insurance bet accepted and win
      addResponseMessage(std::make_shared<InsuranceResultMessage>("Player", ""));

      // Hand lose
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerLoseMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));
      
      // Start Hand
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<InsuranceOfferMessage>("Player", ""));
      addMessage(std::make_shared<InsuranceResponseMessage>("Game", "Rejected"));
      // Insurance bet rejected

      // Hand lose
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerLoseMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));

      // Start Hand
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<InsuranceOfferMessage>("Player", ""));
      addMessage(std::make_shared<InsuranceResponseMessage>("Game", "Accepted"));
      // Insurance bet accepted and lose
      addResponseMessage(std::make_shared<InsuranceResultMessage>("Player", ""));

      // Hand win
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));
      addMessage(std::make_shared<StandMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerWinMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));
      
      // Start Hand
      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<InsuranceOfferMessage>("Player", ""));
      addMessage(std::make_shared<InsuranceResponseMessage>("Game", "Rejected"));
      // Insurance bet rejected

      // Hand Lose
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));
      addMessage(std::make_shared<StandMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerLoseMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));
    }
    
    void setup(std::shared_ptr<MessageSender> msg_sender){
      game_ = std::make_shared<Game>(msg_sender);
      // Must register new game instance on setup.
      msg_sender->registerReceiver(game_);
      deck_ = std::make_shared<InsuranceTestDeck>();
      game_->getTable()->setDeck(deck_);
      setTarget(game_);
    }

  private:
    std::shared_ptr<Deck> deck_;
    std::shared_ptr<Game> game_;
    std::shared_ptr<MessageSender> msg_sender_;
};

