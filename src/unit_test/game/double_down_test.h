#pragma once

#include "message_sender.h"
#include "test.h"
#include "game.h"
#include "double_down_test_deck.h"

class DoubleDownTest : public Test{
  public:
    DoubleDownTest(){
      setName("DoubleDownTest");

      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));
      addMessage(std::make_shared<DoubleDownMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerWinMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));

      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));
      addMessage(std::make_shared<DoubleDownMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerWinMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));

      addMessage(std::make_shared<WagerMessage>("Game", "25"));
      addResponseMessage(std::make_shared<WagerResponseMessage>("Player", "Accepted"));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerChoiceMessage>("Player", ""));
      addMessage(std::make_shared<DoubleDownMessage>("Game", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<TableDataMessage>("Player", ""));
      addResponseMessage(std::make_shared<PlayerBustMessage>("Player", ""));
      addResponseMessage(std::make_shared<RoundCompletedMessage>("Player", ""));
    }
    
    void setup(std::shared_ptr<MessageSender> msg_sender){
      game_ = std::make_shared<Game>(msg_sender);
      // Must register new game instance on setup.
      msg_sender->registerReceiver(game_);
      deck_ = std::make_shared<DoubleDownTestDeck>();
      game_->getTable()->setDeck(deck_);
      setTarget(game_);
    }

  private:
    std::shared_ptr<Deck> deck_;
    std::shared_ptr<Game> game_;
    std::shared_ptr<MessageSender> msg_sender_;
};

