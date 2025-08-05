#pragma once

class WagerControl{
  public:
    WagerControl(){
      setName("WagerControl");
      wager_ = 25;
    }

    void setWager(int wager){
      if(wager < 0){
        wager_ = 0;
      }
      else{
        wager_ = wager;
      }
    }

    int getWager(){
      return wager_;
    }

    std::string getName(){
      return name_;
    }

    void setName(std::string name){
      name_ = name;
    }

  private:
    int wager_;
    std::string name_;
};
