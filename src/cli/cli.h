#pragma once

#include <iostream>
#include "module.h"
#include "utils.h"
#include "bjlogger.h"

#include "cli/messages/to_player/restart_message.h"
#include "cli/messages/to_player/quit_message.h"

#include "player/messages/to_interface/display_balance_message.h"
#include "player/messages/to_interface/display_table_message.h"
#include "player/messages/to_interface/display_hand_result_message.h"
#include "player/messages/to_interface/display_insurance_result_message.h"
#include "player/messages/to_interface/play_response_message.h"
#include "player/messages/to_interface/change_wager_response_message.h"
#include "player/messages/to_interface/cash_in_response_message.h"
#include "player/messages/to_interface/request_input_message.h"
#include "player/messages/to_interface/insufficient_funds_message.h"
#include "player/messages/to_interface/request_insurance_message.h"

#include "cli/states/cli_start_state.h"
#include "cli/states/wait_state.h"
#include "cli/states/playing_hand_state.h"
#include "cli/states/quit_state.h"

#include "cli/handlers/restart_handler.h"
#include "cli/handlers/quit_handler.h"
#include "cli/handlers/display_table_handler.h"
#include "cli/handlers/display_hand_result_handler.h"
#include "cli/handlers/display_insurance_result_handler.h"
#include "cli/handlers/display_balance_handler.h"
#include "cli/handlers/play_response_handler.h"
#include "cli/handlers/change_wager_response_handler.h"
#include "cli/handlers/cash_in_response_handler.h"
#include "cli/handlers/insufficient_funds_handler.h"
#include "cli/handlers/request_input_handler.h"
#include "cli/handlers/request_insurance_handler.h"
#include "cli/handlers/cli_round_completed_handler.h"

class CLI : public Module{
  public:
    CLI(std::shared_ptr<MessageSender> message_sender){
      setName("CLI");
      setMessageSender(message_sender);

      // State Machine
      std::shared_ptr<StateMachine> state_machine = std::make_shared<StateMachine>();
      state_machine->setName("CLI State Machine");
      std::shared_ptr<State> start_state = std::make_shared<CLIStartState>(message_sender, state_machine);
      std::shared_ptr<State> playing_hand_state = std::make_shared<PlayingHandState>(message_sender, state_machine);
      std::shared_ptr<State> wait_state = std::make_shared<WaitState>();
      std::shared_ptr<State> quit_state = std::make_shared<QuitState>();
      state_machine->registerState(start_state);
      state_machine->registerState(playing_hand_state);
      state_machine->registerState(wait_state);
      state_machine->registerState(quit_state);
      state_machine->setCurrentState(start_state);
      setStateMachine(state_machine);

      // Messages
      RestartMessage restart_msg("", "");
      QuitMessage quit_msg("", "");
      DisplayTableMessage display_table_msg("", "");
      DisplayHandResultMessage display_hand_result_msg("", "");
      DisplayInsuranceResultMessage display_insurance_result_msg("", "");
      DisplayBalanceMessage display_balance_msg("", "");
      PlayResponseMessage play_response_msg("", "");
      CashInResponseMessage cash_in_response_msg("", "");
      ChangeWagerResponseMessage change_wager_response_msg("", "");
      RequestInputMessage request_input_msg("", "");
      InsufficientFundsMessage insufficient_funds_msg("", "");
      RequestInsuranceMessage request_insurance_msg("", "");
      CLIRoundCompletedMessage cli_round_completed_msg("", "");

      // Handlers
      std::shared_ptr<MessageHandler> restart_handler = 
        std::make_shared<RestartHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> quit_handler =
        std::make_shared<QuitHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> display_table_handler = 
        std::make_shared<DisplayTableHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> display_hand_result_handler =
        std::make_shared<DisplayHandResultHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> display_insurance_result_handler =
        std::make_shared<DisplayInsuranceResultHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> display_balance_handler = 
        std::make_shared<DisplayBalanceHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> play_response_handler =
        std::make_shared<PlayResponseHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> cash_in_response_handler =
        std::make_shared<CashInResponseHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> change_wager_response_handler =
        std::make_shared<ChangeWagerResponseHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> request_input_handler =
        std::make_shared<RequestInputHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> insufficient_funds_handler =
        std::make_shared<InsufficientFundsHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> request_insurance_handler =
        std::make_shared<RequestInsuranceHandler>(message_sender, state_machine_);

      std::shared_ptr<MessageHandler> cli_round_completed_handler =
        std::make_shared<CLIRoundCompletedHandler>(message_sender, state_machine_);

      // Dispatcher
      std::shared_ptr<Dispatcher> dispatcher = std::make_shared<Dispatcher>(state_machine);
      dispatcher->registerHandler(restart_msg, restart_handler);
      dispatcher->registerHandler(quit_msg, quit_handler);
      dispatcher->registerHandler(display_table_msg, display_table_handler);
      dispatcher->registerHandler(display_hand_result_msg, display_hand_result_handler);
      dispatcher->registerHandler(display_insurance_result_msg, display_insurance_result_handler);
      dispatcher->registerHandler(display_balance_msg, display_balance_handler);
      dispatcher->registerHandler(play_response_msg, play_response_handler);
      dispatcher->registerHandler(cash_in_response_msg, cash_in_response_handler);
      dispatcher->registerHandler(change_wager_response_msg, change_wager_response_handler);
      dispatcher->registerHandler(request_input_msg, request_input_handler);
      dispatcher->registerHandler(insufficient_funds_msg, insufficient_funds_handler);
      dispatcher->registerHandler(request_insurance_msg, request_insurance_handler);
      dispatcher->registerHandler(cli_round_completed_msg, cli_round_completed_handler);
      setDispatcher(dispatcher);
    }

    bool isQuitState(){
      return state_machine_->getCurrentState()->getName() == "QuitState";
    }
};

