#pragma once

#include "message.h"
#include "message_handler.h"
#include "player/messages/to_interface/cli_round_completed_message.h"

class RoundCompletedHandler : public MessageHandler{
  public:
    RoundCompletedHandler(std::shared_ptr<MessageSender> sender,
        std::shared_ptr<StateMachine> state_machine,
        std::shared_ptr<Bank> bank){
        setName("RoundCompletedHandler");
      message_sender_ = sender;
      state_machine_ = state_machine;
      bank_ = bank;
    }

    void handle(Message msg){
      state_machine_->transition("PlayerStartState");
      CLIRoundCompletedMessage cli_round_completed_msg("CLI", "");
      message_sender_->sendMessage(cli_round_completed_msg);
    }

  private:
    std::shared_ptr<MessageSender> message_sender_;
    std::shared_ptr<StateMachine> state_machine_;
    std::shared_ptr<Bank> bank_;
};
