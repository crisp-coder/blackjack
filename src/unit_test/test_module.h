#pragma once

#include "bjlogger.h"
#include "test.h"
#include "module.h"

class TestModule : public Module{
  public:
    TestModule(std::shared_ptr<MessageSender> message_sender){
      setName("TestModule");
      setMessageSender(message_sender);
      failed_ = false;
    }

    /**
     * Set the current test to execute.
     * A test is run when executeTest() is called.
     */
    void setTest(std::shared_ptr<Test> test){
      test_ = test;
    }

    /**
     * This method is invoked when a message is received.
     * It compares the received message to the expected response in
     * the current test.
     * */
    void receiveMessage(Message received_msg){
      logger.LOG(bjlogger::DEBUG, "TestModule received: " + received_msg.getName());
      //logger.LOG(bjlogger::DEBUG, received_msg.getBody());
      std::shared_ptr<Message> expected_msg = test_->getNextResponse();
      if(received_msg.getName() != expected_msg->getName()){
        logger.LOG(bjlogger::DEBUG, "^^Unexpected Message Received.");
        failed_ = true;
      }
    }

    /**
     * This method sends all the messages in the current test.
     * When a response is received, it is compared to the expected response
     * for the current test, and if there is a mismatch, the test is marked
     * failed in the log.
     * Otherwise, the test is passed after all expected messages are received.
     */
    void executeTest(){
      // Reset failed flag per test run.
      failed_ = false;
      logger.LOG(bjlogger::DEBUG, "#############################################");
      logger.LOG(bjlogger::DEBUG, "Test " + test_->getName() + " is executing...");

      // Setup test environment.
      test_->setup(msg_sender_);

      // Send test messages to target.
      std::shared_ptr<Message> msg;

      while(msg = test_->getNextMessage()){
        if(msg->getName() == "NullMessage"){
          break;
        }
        msg_sender_->sendMessage(*msg);

        // Make target process the sent message.
        test_->getTarget()->processMessage();
      }

      // TODO: Verify test has received all expected messages.

      if(failed_){
        logger.LOG(bjlogger::DEBUG, "Test " + test_->getName() + " Failed.");
      }
      else{
        logger.LOG(bjlogger::DEBUG, "Test " + test_->getName() + " Passed.");
      }
      logger.LOG(bjlogger::DEBUG, "#############################################");
    }

  private:
    std::shared_ptr<Test> test_;
    bool failed_;
};
