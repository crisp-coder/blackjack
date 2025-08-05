#pragma once

enum Suit:uint8_t{
  Hearts = 1, 
  Spades = 2, 
  Clubs = 3, 
  Diamonds = 4
};

enum Rank:uint8_t{
  Ace = 1, 
  Two = 2, 
  Three = 3, 
  Four = 4, 
  Five = 5, 
  Six = 6, 
  Seven = 7, 
  Eight = 8, 
  Nine = 9, 
  Ten = 10, 
  Jack = 11, 
  Queen = 12, 
  King = 13
};

class Card{
  public:
    Card(Suit s, Rank r){
      suit_ = s;
      rank_ = r;
      face_up_ = true;
    }
    
    Card(){
      suit_ = Suit::Hearts;
      rank_ = Rank::Queen;
      face_up_ = true;
    }

    std::string getSuitString(){
      switch(suit_){
        case 1: return "Hearts";
        case 2: return "Spades";
        case 3: return "Clubs";
        case 4: return "Diamonds";
        default: return "";
      }
    }

    std::string getRankString(){
      switch(rank_){
        case 1: return "Ace";
        case 2: return "Two";
        case 3: return "Three";
        case 4: return "Four";
        case 5: return "Five";
        case 6: return "Six";
        case 7: return "Seven";
        case 8: return "Eight";
        case 9: return "Nine";
        case 10: return "Ten";
        case 11: return "Jack";
        case 12: return "Queen";
        case 13: return "King";
        default: return "";
      }

    }


    void setRank(Rank r){
      rank_ = r;
    }

    Rank getRank(){
      return rank_;
    }

    void setSuit(Suit s){
      suit_ = s;
    }

    Suit getSuit(){
      return suit_;
    }
    
    void setFaceUp(bool face_up){
      face_up_ = face_up;
    }

    bool isFaceUp(){
      return face_up_;
    }

    int getValue(){
      switch(rank_){
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        case 4: return 4;
        case 5: return 5;
        case 6: return 6;
        case 7: return 7;
        case 8: return 8;
        case 9: return 9;
        case 10: return 10;
        case 11: return 10;
        case 12: return 10;
        case 13: return 10;
        default: return 0;
      }
    }

  private:
    Suit suit_;
    Rank rank_;
    bool face_up_;
};

