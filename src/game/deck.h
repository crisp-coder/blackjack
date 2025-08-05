#pragma once
#include <vector>
#include <memory>
#include "card.h"

class Deck{
  public:
    virtual void reset() = 0; 
    virtual std::shared_ptr<Card> drawCard(bool face_up) = 0; 
    virtual int getCardsRemaining() = 0;
    virtual int getMaxSize() = 0;
    virtual void shuffle() = 0; 
};
