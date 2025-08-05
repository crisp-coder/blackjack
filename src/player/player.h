#pragma once

#include <memory>
#include "message_sender.h"
#include "bjlogger.h"

#include "player/bank.h"
#include "player/wager_control.h"

#include "player/states/player_start_state.h"
#include "player/states/play_state.h"

#include "cli/messages/to_player/cash_in_message.h"
#include "cli/messages/to_player/change_wager_message.h"
#include "cli/messages/to_player/check_balance_message.h"
#include "cli/messages/to_player/play_hand_message.h"
#include "cli/messages/to_player/input_message.h"
#include "cli/messages/to_player/insurance_message.h"
#include "cli/messages/to_player/restart_message.h"
#include "cli/messages/to_player/quit_message.h"

#include "game/messages/to_player/table_data_message.h"
#include "game/messages/to_player/player_choice_message.h"
#include "game/messages/to_player/player_win_message.h"
#include "game/messages/to_player/player_lose_message.h"
#include "game/messages/to_player/player_bust_message.h"
#include "game/messages/to_player/player_push_message.h"
#include "game/messages/to_player/player_surrendered_message.h"
#include "game/messages/to_player/player_blackjack_message.h"
#include "game/messages/to_player/insurance_offer_message.h"
#include "game/messages/to_player/insurance_result_message.h"
#include "game/messages/to_player/round_completed_message.h"
#include "game/messages/to_player/wager_response_message.h"

#include "player/handlers/cash_in_handler.h"
#include "player/handlers/check_balance_handler.h"
#include "player/handlers/change_wager_handler.h"
#include "player/handlers/play_handler.h"
#include "player/handlers/player_choice_handler.h"
#include "player/handlers/player_win_handler.h"
#include "player/handlers/player_lose_handler.h"
#include "player/handlers/player_bust_handler.h"
#include "player/handlers/player_push_handler.h"
#include "player/handlers/player_surrendered_handler.h"
#include "player/handlers/player_blackjack_handler.h"
#include "player/handlers/table_data_handler.h"
#include "player/handlers/input_message_handler.h"
#include "player/handlers/insurance_handler.h"
#include "player/handlers/insurance_offer_handler.h"
#include "player/handlers/insurance_result_handler.h"
#include "player/handlers/round_completed_handler.h"
#include "player/handlers/wager_response_handler.h"

class Player : public Module{
  public:
    Player(std::shared_ptr<MessageSender> message_sender){
      setName("Player");
      setMessageSender(message_sender);
      bank_ = std::make_shared<Bank>();
      wager_control_ = std::make_shared<WagerControl>();

      // Set inital bank balance
      bank_->add(1000);
      wager_control_->setWager(25);

      // State Machine
      std::shared_ptr<StateMachine> state_machine = std::make_shared<StateMachine>();
      state_machine->setName("Player State Machine");
      std::shared_ptr<State> player_start_state = std::make_shared<PlayerStartState>();
      std::shared_ptr<State> play_state = std::make_shared<PlayState>();
      state_machine->registerState(player_start_state);
      state_machine->registerState(play_state);
      state_machine->setCurrentState(player_start_state);
      setStateMachine(state_machine);

      // Messages
      CashInMessage cash_in_msg("", "");
      CheckBalanceMessage check_balance_msg("", "");
      ChangeWagerMessage change_wager_msg("", "");
      PlayHandMessage play_hand_msg("", "");
      TableDataMessage table_data_msg("", "");
      PlayerChoiceMessage player_choice_msg("", "");
      InputMessage input_msg("", ""); 
      RestartMessage restart_msg("", ""); 
      QuitMessage quit_msg("", ""); 

      PlayerWinMessage player_win_msg("", "");
      PlayerLoseMessage player_lose_msg("", "");
      PlayerBustMessage player_bust_msg("", "");
      PlayerPushMessage player_push_msg("", "");
      PlayerSurrenderedMessage player_surrendered_msg("", "");
      PlayerBlackjackMessage player_blackjack_msg("","");

      InsuranceOfferMessage insurance_offer_msg("", "");
      InsuranceMessage insurance_msg("", "");
      InsuranceResultMessage insurance_result_msg("", "");
      RoundCompletedMessage round_completed_msg("", "");
      WagerResponseMessage wager_response_msg("", "");
      
      // Handlers
      std::shared_ptr<MessageHandler> cash_in_handler = 
        std::make_shared<CashInHandler>(message_sender, state_machine, bank_);

      std::shared_ptr<MessageHandler> change_wager_handler = 
        std::make_shared<ChangeWagerHandler>(message_sender, state_machine, bank_, wager_control_);

      std::shared_ptr<MessageHandler> check_balance_handler = 
        std::make_shared<CheckBalanceHandler>(message_sender, state_machine, bank_);

      std::shared_ptr<MessageHandler> play_handler = 
        std::make_shared<PlayHandler>(message_sender, state_machine, bank_, wager_control_);

      std::shared_ptr<MessageHandler> player_choice_handler = 
        std::make_shared<PlayerChoiceHandler>(message_sender, state_machine);

      std::shared_ptr<MessageHandler> input_message_handler =
        std::make_shared<InputMessageHandler>(message_sender, state_machine, bank_, wager_control_);

      std::shared_ptr<MessageHandler> table_data_handler = 
        std::make_shared<TableDataHandler>(message_sender, state_machine);

      std::shared_ptr<MessageHandler> insurance_offer_handler =
        std::make_shared<InsuranceOfferHandler>(message_sender, state_machine, bank_);

      std::shared_ptr<MessageHandler> insurance_handler =
        std::make_shared<InsuranceHandler>(message_sender, state_machine, bank_, wager_control_);

      std::shared_ptr<MessageHandler> insurance_result_handler =
        std::make_shared<InsuranceResultHandler>(message_sender, state_machine, bank_, wager_control_);

      std::shared_ptr<MessageHandler> player_win_handler = 
        std::make_shared<PlayerWinHandler>(message_sender, state_machine, bank_);

      std::shared_ptr<MessageHandler> player_lose_handler = 
        std::make_shared<PlayerLoseHandler>(message_sender, state_machine, bank_);

      std::shared_ptr<MessageHandler> player_bust_handler =
        std::make_shared<PlayerBustHandler>(message_sender, state_machine, bank_);

      std::shared_ptr<MessageHandler> player_push_handler =
        std::make_shared<PlayerPushHandler>(message_sender, state_machine, bank_);

      std::shared_ptr<MessageHandler> player_surrendered_handler = 
        std::make_shared<PlayerSurrenderedHandler>(message_sender, state_machine, bank_);

      std::shared_ptr<MessageHandler> player_blackjack_handler =
        std::make_shared<PlayerBlackjackHandler>(message_sender, state_machine, bank_);

      std::shared_ptr<MessageHandler> round_completed_handler =
        std::make_shared<RoundCompletedHandler>(message_sender, state_machine, bank_);

      std::shared_ptr<MessageHandler> wager_response_handler = 
        std::make_shared<WagerResponseHandler>(message_sender, state_machine);

      // Dispatcher
      std::shared_ptr<Dispatcher> dispatcher = std::make_shared<Dispatcher>(state_machine);
      dispatcher->registerHandler(cash_in_msg, cash_in_handler);
      dispatcher->registerHandler(change_wager_msg, change_wager_handler);
      dispatcher->registerHandler(check_balance_msg, check_balance_handler);
      dispatcher->registerHandler(play_hand_msg, play_handler);
      dispatcher->registerHandler(table_data_msg, table_data_handler);
      dispatcher->registerHandler(player_choice_msg, player_choice_handler);
      dispatcher->registerHandler(input_msg, input_message_handler);
      dispatcher->registerHandler(player_win_msg, player_win_handler);
      dispatcher->registerHandler(player_lose_msg, player_lose_handler);
      dispatcher->registerHandler(player_bust_msg, player_bust_handler);
      dispatcher->registerHandler(player_push_msg, player_push_handler);
      dispatcher->registerHandler(player_surrendered_msg, player_surrendered_handler);
      dispatcher->registerHandler(player_blackjack_msg, player_blackjack_handler);
      dispatcher->registerHandler(insurance_offer_msg, insurance_offer_handler);
      dispatcher->registerHandler(insurance_msg, insurance_handler);
      dispatcher->registerHandler(insurance_result_msg, insurance_result_handler);
      dispatcher->registerHandler(round_completed_msg, round_completed_handler);
      dispatcher->registerHandler(wager_response_msg, wager_response_handler);
      setDispatcher(dispatcher);
    }

  private:
    std::shared_ptr<WagerControl> wager_control_;
    std::shared_ptr<Bank> bank_;
};

