#pragma once

class Bank{
  public:
    Bank(){
      balance_ = 0;
    }

    void reset(){
      balance_ = 0;
    }

    void add(int amount){
      balance_ += amount;
    }

    void withdraw(int amount){
      balance_ -= amount;
      if(balance_ < 0){
        balance_ = 0;
      }
    }

    int getBalance(){
      return balance_;
    }

  private:
    int balance_;
};
