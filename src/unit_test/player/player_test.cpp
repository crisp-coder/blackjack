#include <memory>

#include "message_sender.h"
#include "player.h"

// Log results to logs directory.
#include "bjlogger.h"

bjlogger::Logger logger("logs/player_test_runtime.log");

int main(int argc, char** argv){

  /* Setup */

  std::shared_ptr<MessageSender> msg_sender = std::make_shared<MessageSender>();
  std::shared_ptr<Player> player = std::make_shared<Player>(msg_sender);
  msg_sender->registerModule(player);

  /* Test */
  // Simulate Game messages to player.
  msg_sender->sendMessage();

  /* Results */

  return 0;

}
