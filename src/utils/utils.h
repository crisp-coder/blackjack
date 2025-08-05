#pragma once

#include <iostream>
#include <algorithm>
#include <string>

namespace Utils{

  static inline void ltrim(std::string& str){
    str.erase(
        str.begin(),
        std::find_if(
          str.begin(), 
          str.end(), 
          [](unsigned char c){return !std::isspace(c);}));
  }

  static inline void rtrim(std::string& str){
    str.erase(
        std::find_if(
          str.rbegin(), 
          str.rend(), 
          [](unsigned char c){return !std::isspace(c);}).base(), 
        str.end());
  }

  static inline void trim(std::string& str){
    ltrim(str);
    rtrim(str);
  }

  static inline void toLower(std::string& str){
    std::transform(
        str.begin(), 
        str.end(),
        str.begin(),
        [](unsigned char ch ){
        return std::tolower(ch);});
  }

  static void receiveInput(std::string& input){
    std::getline(std::cin, input);
    trim(input);
    toLower(input);
  }

  static bool isInteger(std::string source){
    trim(source);

    // Scan first char
    if(source[0] != '-' && 
        source[0] != '+'  &&
        source[0] != '1'  &&
        source[0] != '2'  &&
        source[0] != '3'  &&
        source[0] != '4'  &&
        source[0] != '5'  &&
        source[0] != '6'  &&
        source[0] != '7'  &&
        source[0] != '8'  &&
        source[0] != '9'  &&
        source[0] != '0'){
      return false;
    }
    
    // Scan remaining chars
    for(int i = 1; i < source.length(); i++){
      if( source[i] != '1'  &&
          source[i] != '2'  &&
          source[i] != '3'  &&
          source[i] != '4'  &&
          source[i] != '5'  &&
          source[i] != '6'  &&
          source[i] != '7'  &&
          source[i] != '8'  &&
          source[i] != '9'  &&
          source[i] != '0'){
        return false;
      }
    }
    return true;
  }
}

