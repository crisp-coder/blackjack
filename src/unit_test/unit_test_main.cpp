#include <iostream>
#include <memory>

#include "message_sender.h"
#include "test_module.h"
#include "game.h"

// Include each test to run. 
// GAME TESTS
#include "zero_wager_test.h"
#include "empty_wager_test.h"
#include "negative_wager_test.h"
#include "nan_wager_test.h"
#include "min_wager_test.h"
#include "max_wager_test.h"

#include "stand_test.h"
#include "hit_test.h"
#include "double_down_test.h"
#include "split_test.h"
#include "insurance_test.h"
#include "surrender_test.h"
#include "push_test.h"
#include "bust_test.h"
#include "lose_test.h"
#include "win_test.h"
#include "blackjack_win_test.h"
#include "blackjack_push_test.h"

// PLAYER TESTS

// CLI TESTS

// Include logger for logging test results
#include "bjlogger.h"
bjlogger::Logger logger("logs/game_test_runtime.log", bjlogger::LOG_LEVEL::DEBUG);

int main(int argc, char** argv){
  logger.LOG(bjlogger::LOG_LEVEL::INFO, "BEGIN TESTS");

  std::shared_ptr<MessageSender> msg_sender = std::make_shared<MessageSender>();
  std::shared_ptr<TestModule> test_module = std::make_shared<TestModule>(msg_sender);
  // Test module is spoofing the player module.
  test_module->setName("Player");
  msg_sender->registerReceiver(test_module);

  logger.LOG(bjlogger::LOG_LEVEL::INFO, "-------GAME UNIT TESTS------");

  // Wager Tests
  std::shared_ptr<Test> zero_wager_test = std::make_shared<ZeroWagerTest>();
  test_module->setTest(zero_wager_test);
  test_module->executeTest();

  std::shared_ptr<Test> empty_wager_test = std::make_shared<EmptyWagerTest>();
  test_module->setTest(empty_wager_test);
  test_module->executeTest();

  std::shared_ptr<Test> neg_wager_test = std::make_shared<NegativeWagerTest>();
  test_module->setTest(neg_wager_test);
  test_module->executeTest();

  std::shared_ptr<Test> nan_wager_test = std::make_shared<NaNWagerTest>();
  test_module->setTest(nan_wager_test);
  test_module->executeTest();

  std::shared_ptr<Test> max_wager_test = std::make_shared<MaxWagerTest>();
  test_module->setTest(max_wager_test);
  test_module->executeTest();

  std::shared_ptr<Test> min_wager_test = std::make_shared<MinWagerTest>();
  test_module->setTest(min_wager_test);
  test_module->executeTest();

  // Stand Tests
  std::shared_ptr<Test> empty_stand_test = std::make_shared<StandTest>();
  test_module->setTest(empty_stand_test);
  test_module->executeTest();

  // Hit Tests 
  std::shared_ptr<Test> empty_hit_test = std::make_shared<HitTest>();
  test_module->setTest(empty_hit_test);
  test_module->executeTest();

  // Double Down Tests
  std::shared_ptr<Test> double_down_test = std::make_shared<DoubleDownTest>();
  test_module->setTest(double_down_test);
  test_module->executeTest();

  // Split Tests
  std::shared_ptr<Test> split_test = std::make_shared<SplitTest>();
  test_module->setTest(split_test);
  test_module->executeTest();

  // Insurance Tests
  std::shared_ptr<Test> insurance_test = std::make_shared<InsuranceTest>();
  test_module->setTest(insurance_test);
  test_module->executeTest();

  // Surrender Tests
  std::shared_ptr<Test> surrender_test = std::make_shared<SurrenderTest>();
  test_module->setTest(surrender_test);
  test_module->executeTest();

  // WinTest
  std::shared_ptr<Test> win_test = std::make_shared<WinTest>();
  test_module->setTest(win_test);
  test_module->executeTest();

  // LoseTest
  std::shared_ptr<Test> lose_test = std::make_shared<LoseTest>();
  test_module->setTest(lose_test);
  test_module->executeTest();

  // PushTest
  std::shared_ptr<Test> push_test = std::make_shared<PushTest>();
  test_module->setTest(push_test);
  test_module->executeTest();

  // BustTest
  std::shared_ptr<Test> bust_test = std::make_shared<BustTest>();
  test_module->setTest(bust_test);
  test_module->executeTest();

  // Blackjack Tests
  std::shared_ptr<Test> blackjack_win_test = std::make_shared<BlackjackWinTest>();
  test_module->setTest(blackjack_win_test);
  test_module->executeTest();

  // Blackjack with push test
  std::shared_ptr<Test> blackjack_push_test = std::make_shared<BlackjackPushTest>();
  test_module->setTest(blackjack_push_test);
  test_module->executeTest();

  logger.LOG(bjlogger::LOG_LEVEL::INFO, "-------PLAYER UNIT TESTS------");

  logger.LOG(bjlogger::LOG_LEVEL::INFO, "END TESTS");
  
  return 0;
}

