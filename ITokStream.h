/** @file ITokStream.h
 @author Anthony Campos
 @date 12/07/2021
 This header class file implements a tokenizer that tokenizes a
   inputted algebraic expessions into its components */


#pragma once

// include libraries
#include "Token.h"
#include <istream>
#include <iostream>


/**  ITokStream */
class ITokStream {



public:

   /** ITokStream Public Methods */

   /** ITokStream constructor */
   ITokStream(std::istream& inputStream);

   /** overloaded operator>> 
   @pre must be a Token object
   @post Token object's values retrieved from the istream and set
   @return istream */
   ITokStream& operator>>(Token& rhs);

   /** overloaded bool()
   @ returns whether the istream contains any errors*/
   explicit operator bool() const;


private:

   /**  ITokStream Private attribute */

   //stores the reference to the provided std::istream
   std::istream& is_;

   /**  ITokStream Private methods */

    /** determineTokenType
    @post the token's type_ set per the provided char
    @param char [input], curToken [Token]*/
   void determineTokenType(const char input, Token& curToken);

}; // end of ITokStream

