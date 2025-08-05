#include <iostream>
#include <memory>

#include "message_sender.h"
#include "module.h"
#include "game.h"
#include "player.h"
#include "cli.h"

// Log results to logs directory.
#include "bjlogger.h"

bjlogger::Logger logger("logs/cli_test_runtime.log");

int main(int argc, char** argv){

  /* Setup */

  std::shared_ptr<MessageSender> msg_sender = std::make_shared<MessageSender>();
  std::shared_ptr<Module> game = std::make_shared<Game>(msg_sender);
  msg_sender->registerModule(game);

  /* Test */

  // Player to Game interactions
  // Simulate Player messages to Game.
  msg_sender->sendMessage();

  /* Results */

  return 0;

}
