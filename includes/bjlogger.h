#pragma once
#include <string>
#include <fstream>

namespace bjlogger{
  enum LOG_LEVEL {
    ERROR = 1,
    WARN = 2, 
    DEBUG = 3, 
    INFO = 4 
  };

  class Logger{
    public:
      Logger(std::string filename, LOG_LEVEL mask){
        mask_ = mask;
        logFile.open(filename.c_str(), std::ios::app);
        if(!logFile.is_open()){
          std::cout << "Failed to open log file." << std::endl;
        }
      }

      Logger(std::string filename){
        mask_ = INFO;
        logFile.open(filename.c_str(), std::ios::app);
        if(!logFile.is_open()){
          std::cout << "Failed to open log file." << std::endl;
        }
      }

      ~Logger(){
        logFile.close();
      }

      /**
       * Simply prints message to log file.
       * */
      void LOG(std::string msg){
        logFile << msg << std::endl;
      }

      /**
       * Logs a message with a level used for filtering.
       * If the logger level is lower than the level of the message,
       * the message will NOT be logged.
       * */
      void LOG(LOG_LEVEL level, std::string msg){
        if(mask_ >= level){
          switch(level){
            case INFO: 
              logFile << "INFO: ";
              break;
            case DEBUG: 
              logFile << "DEBUG: ";
              break;
            case WARN: 
              logFile << "WARN: ";
              break;
            case ERROR: 
              logFile << "ERROR: ";
              break;
            default: { /* do nothing.*/}
          }
          logFile << msg << std::endl;
        }
      }

      /**
       * Simply prints message to log file.
       * */
      std::ofstream& operator<<(std::string msg){
        if(mask_ >= message_level){
          logFile << msg;
        }
        return logFile;
      }

      /**
       * Change Logger message level using stream insertion.
       * Also prints the log level message to log file.
       *
       * Usage: logger << log_level << message << std::endl;
       * */
      std::ofstream& operator<<(LOG_LEVEL level){
        message_level = level;
        switch(level){
          case INFO: 
            logFile << "INFO: ";
            break;
          case DEBUG: 
            logFile << "DEBUG: ";
            break;
          case WARN: 
            logFile << "WARN: ";
            break;
          case ERROR: 
            logFile << "ERROR: ";
            break;
          default: { /* do nothing.*/}
        }
        return logFile;
      }

    private:
      std::ofstream logFile;
      LOG_LEVEL mask_;
      LOG_LEVEL message_level;
  };

}

extern bjlogger::Logger logger;
