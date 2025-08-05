#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "card.h"
#include "deck.h"

class SurrenderTestDeck : public Deck{
  public:
    SurrenderTestDeck(){
      max_size_ = 52; 
      init();
    }

    void reset(){
      cards_.clear();
      init();
    }

    void init(){
      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Five)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Seven)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Ace)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Jack)));

      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Two)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Ace)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Four)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Queen)));

      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Six)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Eight)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Nine)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Ten)));

      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Two)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::Queen)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Hearts, Rank::King)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Ace)));

      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Three)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Four)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Five)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Six)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Seven)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Eight)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Nine)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Ten)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::Jack)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Spades, Rank::King)));

      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Two)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Three)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Four)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Five)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Six)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Seven)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Eight)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Nine)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Ten)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Jack)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::Queen)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Clubs, Rank::King)));

      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Ace)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Two)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Three)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Four)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Five)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Six)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Seven)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Eight)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Nine)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Ten)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Jack)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::Queen)));
      cards_.push_back(std::make_shared<Card>(Card(Suit::Diamonds, Rank::King)));
    }

    std::vector<std::shared_ptr<Card>> getCards(){
      return cards_;
    }

    void shuffle(){
    }

    int getCardsRemaining(){
      return cards_.size();
    }

    std::shared_ptr<Card> drawCard(bool face_up){
      std::shared_ptr<Card> card = cards_[0];
      card->setFaceUp(face_up);
      cards_.erase(cards_.begin());
      return card;
    }

    int getMaxSize(){
      return max_size_;
    }

  private:
    std::vector<std::shared_ptr<Card>> cards_;
    int max_size_;
};


