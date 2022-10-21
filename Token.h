/** @file Token.h
 @author Anthony Campos
 @date 12/07/2021
 This header class file implements a  data structure known as a
   Token that holds a TokType and a std::string value */

#pragma once

// include libraries
#include <string>

/**  Global Variable */
enum class TokType { addminusop, muldivop, powop, variable, number, lparen, rparen, assign, newline, end, unknown };

/**  Token Struct */

class Token {

public:
   /**  Token Public Methods */

   /** Token constructors  */
   Token(TokType t = TokType::unknown, std::string v = "");

   /** Accessors */

   /** getValue
   @return std::string value_*/
   std::string getValue() const;

   /** getType
   @return TokType type_*/
   TokType getType() const;

   /** mutators */

   /** setValue
   @post If successful, value_ is set to std::string value
   @return true if value was set*/
   bool setValue(std::string value);

   /** setType
   @post if successful, type_ is set to the TokType std::string
   @return true if type was set*/
   bool setType(TokType type);

private:
   /**  Token private attribute */

   // holds the token type
   TokType type_;
   // hold the token value 
   std::string value_;

}; // end of Token

