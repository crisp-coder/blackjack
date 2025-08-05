#pragma once

#include <string>
#include <sstream>
#include <vector>

#include "hand.h"
#include "deck.h"
#include "dealer.h"
#include "rule_book.h"

class Table{
  public:
    Table(){
      hand_indx_ = 0;
      player_hands_.push_back(std::make_shared<Hand>());
      dealer_hand_ = std::make_shared<Hand>();
      rule_book_ = std::make_shared<RuleBook>();
    }

    void resetIndex(){
      hand_indx_ = 0;
    }

    bool pollHands(){
      bool hand_in_play = false;
      for(auto h : player_hands_){
        if(!rule_book_->isBust(h) && !rule_book_->isSurrendered(h)){
          hand_in_play = true;
        }
      }
      return hand_in_play;
    }

    bool nextHand(){
      if(hand_indx_ < player_hands_.size()-1){
        hand_indx_ += 1;
        return true;
      }
      else{
        return false;
      }
    }

    void surrenderPlayerHand(){
      player_hands_[hand_indx_]->setSurrendered(true); 
    }

    void setPlayerWager(int amount){
      player_hands_[hand_indx_]->setWager(amount);
    }

    void splitPlayerHand(){
      auto hand = player_hands_[hand_indx_];
      std::shared_ptr<Hand> new_hand = std::make_shared<Hand>();
      new_hand->setWager(hand->getWager());
      if(hand->getSize() > 1){
        new_hand->receiveCard(hand->removeCard());
        dealer_->dealCard(hand, deck_, true);
        dealer_->dealCard(new_hand, deck_, true);
      }
      else{
        logger.LOG(bjlogger::ERROR, "Game::Table: cannot split hand with less than 2 cards.");
      }
      player_hands_.push_back(new_hand);
    }

    int getPlayerWager(){
      return player_hands_[hand_indx_]->getWager();
    }

    void setDealer(std::shared_ptr<Dealer> dealer){
      dealer_ = dealer;
    }

    void setDeck(std::shared_ptr<Deck> deck){
      deck_ = deck;
    }

    std::shared_ptr<Deck> getDeck(){
      return deck_;
    }

    void setRuleBook(std::shared_ptr<RuleBook> rule_book){
      rule_book_ = rule_book;
    }

    // Player Turn option conditions
    bool playerCanHit(){
      return rule_book_->canHit(player_hands_[hand_indx_]); 
    }

    bool playerCanStand(){
      return rule_book_->canStand(player_hands_[hand_indx_]);
    }

    bool playerCanSplit(){
      return rule_book_->canSplit(player_hands_[hand_indx_]);
    }

    bool playerCanSurrender(){
      return rule_book_->canSurrender(player_hands_[hand_indx_], dealer_hand_);
    }

    bool playerCanInsure(){
      return rule_book_->canInsure(dealer_hand_);
    }

    bool playerCanDoubleDown(){
      return playerCanHit() && player_hands_[hand_indx_]->getSize() == 2;
    }

    // Player win conditions
    bool checkPlayerSurrendered(){
      return rule_book_->isSurrendered(player_hands_[hand_indx_]);
    }

    bool checkPlayerPush(){
      return rule_book_->isPush(player_hands_[hand_indx_], dealer_hand_);
    }

    bool checkPlayerWin(){
      return rule_book_->isWin(player_hands_[hand_indx_], dealer_hand_);
    }

    bool checkPlayerNatural(){
      return rule_book_->isNatural(player_hands_[hand_indx_]);
    }

    bool checkPlayerHas21(){
      return rule_book_->is21(player_hands_[hand_indx_]);
    }

    bool checkPlayerBust(){
      return rule_book_->isBust(player_hands_[hand_indx_]);
    }

    bool checkDealerBust(){
      return rule_book_->isBust(dealer_hand_);
    }

    bool checkDealerNatural(){
      return rule_book_->isNatural(dealer_hand_);
    }

    bool checkDealerHas21(){
      return rule_book_->is21(dealer_hand_);
    }

    // Deal card logic
    bool dealerCanDraw(){
      return rule_book_->canDraw(dealer_hand_);
    }

    void setDealerHoleCardFaceUp(){
      dealer_->setCardsFaceUp(dealer_hand_);
    }

    void dealCardToPlayer(bool face_up){
      dealer_->dealCard(player_hands_[hand_indx_], deck_, face_up);
    }

    void dealCardToDealer(bool face_up){
      dealer_->dealCard(dealer_hand_, deck_, face_up);
    }

    bool isTimeToShuffle(){
      return rule_book_->isTimeToShuffle(deck_);
    }

    void reset(){
      clearHands();
      deck_->reset();
    }

    void shuffleDeck(){
      deck_->reset();
      deck_->shuffle();
    }

    void clearHands(){
      dealer_hand_->clear();
      player_hands_.clear();
      hand_indx_ = 0;
      player_hands_.push_back(std::make_shared<Hand>());
    }

    std::string encode(){
      std::ostringstream os;
      int count = 0;
      for(auto h : player_hands_){
        count++;
        os << "***********Player Hand " << count << "**************\n";
        for(auto c : h->getCards()){
          if(c->isFaceUp()){
            os << "Player: " << c->getSuitString() << " " << c->getRankString() << "\n";
          }
          else{
            os << "Player: ? ? \n";
          }

        }
        os << rule_book_->getValue(h) << "\n";
      }

      bool hole_card_up = true;
      os << "**************Dealer************\n";
      for(auto c : dealer_hand_->getCards()){
        if(c->isFaceUp()){
          os << "Dealer: " << c->getSuitString() << " " << c->getRankString() << "\n";
        }
        else{
          os << "Dealer: Hole Card\n";
          hole_card_up = false;
        }
      }

      if(hole_card_up){
        os << rule_book_->getValue(dealer_hand_) << "\n";
      }

      return os.str();
    }

  private:
    std::vector<std::shared_ptr<Hand>> player_hands_;
    int hand_indx_;

    std::shared_ptr<Hand> dealer_hand_;
    std::shared_ptr<Dealer> dealer_;
    std::shared_ptr<Deck> deck_;
    std::shared_ptr<RuleBook> rule_book_;
};


