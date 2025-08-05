#pragma once

#include <ctime>
#include "bjlogger.h"

#include "module.h"
#include "message_sender.h"
#include "state_machine.h"
#include "dispatcher.h"

#include "game/deck.h"
#include "game/single_deck.h"
#include "game/double_deck.h"
#include "game/table.h"

#include "game/states/game_start_state.h"
#include "game/states/insurance_state.h"
#include "game/states/wager_state.h"
#include "game/states/deal_state.h"
#include "game/states/player_turn_state.h"
#include "game/states/dealer_turn_state.h"
#include "game/states/showdown_state.h"

#include "player/messages/to_game/wager_message.h"
#include "player/messages/to_game/hit_message.h"
#include "player/messages/to_game/double_down_message.h"
#include "player/messages/to_game/stand_message.h"
#include "player/messages/to_game/split_message.h"
#include "player/messages/to_game/surrender_message.h"
#include "player/messages/to_game/insurance_response_message.h"

// TODO: Need to refactor this
#include "cli/messages/to_player/restart_message.h"
#include "cli/messages/to_player/quit_message.h"

#include "game/handlers/wager_handler.h"
#include "game/handlers/hit_handler.h"
#include "game/handlers/double_down_handler.h"
#include "game/handlers/stand_handler.h"
#include "game/handlers/split_handler.h"
#include "game/handlers/surrender_handler.h"
#include "game/handlers/game_restart_handler.h"
#include "game/handlers/game_quit_handler.h"
#include "game/handlers/insurance_response_handler.h"

class Game : public Module{
  public:
    Game(std::shared_ptr<MessageSender> message_sender){
      srand(time(NULL));
      setName("Game");
      setMessageSender(message_sender);

      // Game objects
      std::shared_ptr<Table> table = std::make_shared<Table>();
      std::shared_ptr<Deck> deck = std::make_shared<DoubleDeck>();
      deck->shuffle();
      table->setDeck(deck);
      setTable(table);

      // State machine
      std::shared_ptr<StateMachine> state_machine = std::make_shared<StateMachine>();
      state_machine->setName("Game State Machine");
      std::shared_ptr<State> game_start_state = std::make_shared<GameStartState>(message_sender, state_machine, table);
      std::shared_ptr<State> insurance_state = std::make_shared<InsuranceState>(message_sender, state_machine, table);
      std::shared_ptr<State> wager_state = std::make_shared<WagerState>(message_sender, state_machine, table);
      std::shared_ptr<State> deal_state = std::make_shared<DealState>(message_sender, state_machine, table);
      std::shared_ptr<State> player_turn_state = std::make_shared<PlayerTurnState>(message_sender, state_machine, table);
      std::shared_ptr<State> dealer_turn_state = std::make_shared<DealerTurnState>(message_sender, state_machine, table);
      std::shared_ptr<State> showdown_state = std::make_shared<ShowdownState>(message_sender, state_machine, table);
      state_machine->registerState(game_start_state);
      state_machine->registerState(insurance_state);
      state_machine->registerState(wager_state);
      state_machine->registerState(deal_state);
      state_machine->registerState(player_turn_state);
      state_machine->registerState(dealer_turn_state);
      state_machine->registerState(showdown_state);
      state_machine->setCurrentState(game_start_state);
      setStateMachine(state_machine);

      // Messages
      WagerMessage wager_msg("", "");
      HitMessage hit_msg("", "");
      DoubleDownMessage double_down_msg("", "");
      StandMessage stand_msg("", "");
      SurrenderMessage surrender_msg("", "");
      SplitMessage split_msg("", "");
      RestartMessage restart_msg("", "");
      QuitMessage quit_msg("", "");
      InsuranceResponseMessage insurance_resp_msg("", "");

      // Handlers
      std::shared_ptr<MessageHandler> wager_handler =
        std::make_shared<WagerHandler>(message_sender, state_machine, table);

      std::shared_ptr<MessageHandler> hit_handler =
        std::make_shared<HitHandler>(message_sender, state_machine, table);

      std::shared_ptr<MessageHandler> double_down_handler =
        std::make_shared<DoubleDownHandler>(message_sender, state_machine, table);

      std::shared_ptr<MessageHandler> stand_handler =
        std::make_shared<StandHandler>(message_sender, state_machine, table);

      std::shared_ptr<MessageHandler> split_handler =
        std::make_shared<SplitHandler>(message_sender, state_machine, table);

      std::shared_ptr<MessageHandler> surrender_handler =
        std::make_shared<SurrenderHandler>(message_sender, state_machine, table);

      std::shared_ptr<MessageHandler> game_restart_handler =
        std::make_shared<GameRestartHandler>(message_sender, state_machine, table);

      std::shared_ptr<MessageHandler> game_quit_handler = 
        std::make_shared<GameQuitHandler>(message_sender, state_machine, table);

      std::shared_ptr<MessageHandler> insurance_resp_handler = 
        std::make_shared<InsuranceResponseHandler>(message_sender, state_machine, table);

      // Dispatcher
      std::shared_ptr<Dispatcher> dispatcher = std::make_shared<Dispatcher>(state_machine);
      dispatcher->registerHandler(wager_msg, wager_handler);
      dispatcher->registerHandler(hit_msg, hit_handler);
      dispatcher->registerHandler(double_down_msg, double_down_handler);
      dispatcher->registerHandler(stand_msg, stand_handler);
      dispatcher->registerHandler(split_msg, split_handler);
      dispatcher->registerHandler(surrender_msg, surrender_handler);
      dispatcher->registerHandler(restart_msg, game_restart_handler);
      dispatcher->registerHandler(quit_msg, game_quit_handler);
      dispatcher->registerHandler(insurance_resp_msg, insurance_resp_handler);
      setDispatcher(dispatcher);
    }

    void setTable(std::shared_ptr<Table> table){
      table_ = table;
    }

    std::shared_ptr<Table> getTable(){
      return table_;
    }

  private:
    std::shared_ptr<Table> table_;
};
