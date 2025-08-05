#pragma once

#include <memory>

#include "deck.h"
#include "hand.h"

class Dealer{
  public:
    Dealer(){}

    void dealCard(std::shared_ptr<Hand> hand, std::shared_ptr<Deck> deck, bool face_up){
      hand->receiveCard(deck->drawCard(face_up));
    }

    void setCardsFaceUp(std::shared_ptr<Hand> hand){
      for(auto c : hand->getCards()){
        c->setFaceUp(true);
      }
    }
};
