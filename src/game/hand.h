#pragma once

#include <vector>
#include <memory>
#include "card.h"

class Hand{
  public:
    Hand(){
      wager_ = 0;
      surrendered_ = false;
    }

    void receiveCard(std::shared_ptr<Card> card){
      cards_.push_back(card);
    }

    std::shared_ptr<Card> removeCard(){
      if(cards_.size() > 0){
        std::shared_ptr<Card> card = cards_[cards_.size()-1];
        cards_.erase(cards_.begin());
        return card;
      }
      else{
        // TODO: Log error
        std::cout << "Removing card from empty hand..." << std::endl;
        return std::make_shared<Card>();
      }
    }

    std::vector<std::shared_ptr<Card>> getCards(){
      return cards_;
    }

    void clear(){
      cards_.clear();
    }

    void setWager(int amount){
      wager_ = amount;
    }

    int getWager(){
      return wager_;
    }

    int getSize(){
      return cards_.size(); 
    }

    bool hasAceUp(){
      for(auto c : cards_){
        if(c->getRank() == 1 && c->isFaceUp()){
          return true;
        }
      }
      return false;
    }

    bool isSurrendered(){
      return surrendered_;
    }

    void setSurrendered(bool input){
      surrendered_ = input;
    }

  private:
    std::vector<std::shared_ptr<Card>> cards_;
    int wager_;
    bool surrendered_;
};
