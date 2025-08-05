#include <iostream>
#include <chrono>
#include <thread>
#include <memory>

#include "message_sender.h"
#include "module.h"
#include "game.h"
#include "player.h"
#include "cli.h"

#include "bjlogger.h"

// Make global logger and open log file in logs directory
bjlogger::Logger logger("logs/blackjack_runtime.log");

int main(int argc, char** argv){

  logger.LOG("Starting Blackjack CLI Service...");

  // Make message sender. Routes messages between modules.
  std::shared_ptr<MessageSender> msg_sender = std::make_shared<MessageSender>();

  // Make modules. Modules send messages through sender.
  std::shared_ptr<Module> game = std::make_shared<Game>(msg_sender);
  std::shared_ptr<Module> player = std::make_shared<Player>(msg_sender);
  std::shared_ptr<Module> cli = std::make_shared<CLI>(msg_sender);

  // Register modules with sender so they can receive messages.
  msg_sender->registerReceiver(cli);
  msg_sender->registerReceiver(player);
  msg_sender->registerReceiver(game);

  RestartMessage restart_msg("CLI", "");
  msg_sender->sendMessage(restart_msg);

  // Handle queued messages every tick.
  while(true){
    if(cli->isQuitState()){
      break;
    }
    player->processMessage();
    game->processMessage();
    cli->processMessage();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  logger.LOG("Exiting Blackjack service ...");
  return 0;
}

