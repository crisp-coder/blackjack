#pragma once

#include <string>
#include "state.h"
#include "message_sender.h"
#include "state_machine.h"

#include "cli/messages/to_player/play_hand_message.h"
#include "cli/messages/to_player/restart_message.h"
#include "cli/messages/to_player/quit_message.h"

#include "utils.h"

class CLIStartState: public State{
  public:
    CLIStartState(std::shared_ptr<MessageSender> message_sender,
        std::shared_ptr<StateMachine> state_machine){
      setName("CLIStartState");
      message_sender_ = message_sender;
      state_machine_ = state_machine;
    }

    bool accept(Message msg){
      std::string name = msg.getName();
      return name == "RestartMessage" || 
        name == "DisplayBalanceMessage"||
        name == "DisplayHandResultMessage"||
        name == "InsufficientFundsMessage"||
        name == "QuitMessage";
    }

    void onEntry(){
      while(true){
        std::cout << "Main Menu: <play> <cash in> <change wager> <check balance> <quit> <help>" << std::endl;
        std::string input = "";
        Utils::receiveInput(input);
        if(input == "play"){
          PlayHandMessage play_hand_msg("Player", "");
          message_sender_->sendMessage(play_hand_msg);
          state_machine_->transition("WaitState");
          break;
        }
        else if(input == "cash in"){
          cashIn();
          break;
        }
        else if(input == "change wager"){
          changeWager();
          break;
        }
        else if(input == "check balance"){
          CheckBalanceMessage check_balance_msg("Player", "");
          message_sender_->sendMessage(check_balance_msg);
          break;
        }
        else if(input == "help"){
          std::cout << "Type \"play\" to begin a round of blackjack." << std::endl;
          std::cout << "Type \"check balance\" to display player balance." << std::endl;
          std::cout << "Type \"cash in\" to add money to player balance." << std::endl;
          std::cout << "Type \"change wager\" to set a new wager amount per hand." << std::endl;
          std::cout << "Type \"quit\" to exit the game." << std::endl;
        }
        else if(input == "quit") {
          QuitMessage quit_msg("Player", "");
          message_sender_->sendMessage(quit_msg);
          quit_msg.setRecipient("Game");
          message_sender_->sendMessage(quit_msg);
          state_machine_->transition("QuitState");
          break;
        }
        else{
          std::cout << "Invalid option." << std::endl; 
        }
      }
    }

    void cashIn(){
      while(true){
        std::cout << "Enter an amount betwwn 25 and 10000 to cash in: " << std::endl;
        std::string input = "";
        Utils::receiveInput(input);
        if(Utils::isInteger(input)){
          int amount = std::stoi(input);
          if((amount >= 25) && (amount <= 10000)){
            CashInMessage cash_in_msg("Player", std::to_string(amount)); 
            message_sender_->sendMessage(cash_in_msg);
            state_machine_->transition("WaitState");
            break;

          }
          else{
            std::cout << "Invalid amount. Min is 25. Max is 10000." << std::endl;
          }
        }
        else{
          std::cout << "Input is not a number, try again." << std::endl;
        }
      }
    }

    void changeWager(){
      while(true){
        std::cout << "Enter an amount between 25 and 3000 to wager: " << std::endl;
        std::string input = "";
        Utils::receiveInput(input);
        if(Utils::isInteger(input)){
          int amount = std::stoi(input);
          if((amount >= 25) && (amount <= 3000)){
            ChangeWagerMessage 
              change_wager_msg("Player", std::to_string(amount));
            message_sender_->sendMessage(change_wager_msg);
            state_machine_->transition("WaitState");
            break;
          }
          else{
            std::cout << "Invalid amount. Min is 25. Max is 3000." << std::endl;
          }
        }
        else{
          std::cout << "Input is not a number, try again." << std::endl;
        }
      }
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
};

