#pragma once

#include <iostream>

class RuleBook{
  public:
    RuleBook(){}

    bool isSurrendered(std::shared_ptr<Hand> hand){
      return hand->isSurrendered();
    }
    
    bool is21(std::shared_ptr<Hand> hand){
      return getValue(hand) == 21;
    }

    bool isNatural(std::shared_ptr<Hand> hand){
      return getValue(hand) == 21 && hand->getSize() == 2;
    }

    bool isPush(std::shared_ptr<Hand> hand_a,
      std::shared_ptr<Hand> hand_b){
      return !isBust(hand_a) && !isBust(hand_b) && (getValue(hand_a) == getValue(hand_b));
    }

    bool isWin(std::shared_ptr<Hand> hand_a,
      std::shared_ptr<Hand> hand_b){
      return (!isBust(hand_a) && isBust(hand_b)) ||
        (!isBust(hand_a) && !isBust(hand_b) && getValue(hand_a) > getValue(hand_b));  
    }

    bool isBust(std::shared_ptr<Hand> hand){
      return getValue(hand) > 21;
    }

    bool isTimeToShuffle(std::shared_ptr<Deck> deck){
      // TODO: refactor for multi deck shoes.
      return deck->getCardsRemaining() < deck->getMaxSize()/2;
    }   

    // Dealer turn options
    bool canDraw(std::shared_ptr<Hand> dealer_hand){
      return (getValue(dealer_hand) < 17) || (getValue(dealer_hand) == 17 && !isHardValue(dealer_hand));
    }

    // Player Turn option conditions
    bool canHit(std::shared_ptr<Hand> hand){
      return getValue(hand) < 21;
    }

    bool canStand(std::shared_ptr<Hand> hand){
      return true;
    }

    bool canSplit(std::shared_ptr<Hand> hand){
      if(hand->getSize() == 2){
        auto cards = hand->getCards();
        return cards[0]->getValue() == cards[1]->getValue();
      }

      return false;
    }

    // Can surrender when dealer is showing an ace or a 10 but doesnt have blackjack.
    bool canSurrender(std::shared_ptr<Hand> player_hand, std::shared_ptr<Hand> dealer_hand){
      return player_hand->getSize() == 2 && getValue(player_hand) != 21 && 
            (getUpCardValue(dealer_hand) == 11 || getUpCardValue(dealer_hand) == 10) && 
            !is21(dealer_hand);
    }

    bool canInsure(std::shared_ptr<Hand> dealer_hand){
      auto cards = dealer_hand->getCards();
      return !(cards[0]->isFaceUp()) && (cards[1]->isFaceUp() && cards[1]->getRank() == 1);
    }

    bool canDoubleDown(std::shared_ptr<Hand> hand){
      return hand->getSize() == 2 && getValue(hand) < 21;
    }

    int getUpCardValue(std::shared_ptr<Hand> dealer_hand){
      for(auto c : dealer_hand->getCards()){
        if(c->isFaceUp()){
          return c->getValue();
        }
      }
      return 0;
    }

    int getValue(std::shared_ptr<Hand> hand){
      int sum = 0;
      int num_hard_aces = 0;
      auto cards = hand->getCards();
      for(auto c : cards){
        if(c->getRank() == 1){
          num_hard_aces++;  
        }
        sum += c->getValue();
      }

      while(sum + 10 <=21 && num_hard_aces){
        sum += 10;
        num_hard_aces--;
      }

      return sum;
    }

    bool isHardValue(std::shared_ptr<Hand> hand){
      int sum = 0;
      int num_aces = 0;
      int num_soft_aces = 0;
      auto cards = hand->getCards();
      for(auto c : cards){
        if(c->getRank() == 1){
          num_aces++;
        }
        sum += c->getValue();
      }

      while(sum + 10 <= 21 && num_aces){
        sum += 10;
        num_aces--;
        num_soft_aces++;
      }

      return num_soft_aces == 0;
    }
};

