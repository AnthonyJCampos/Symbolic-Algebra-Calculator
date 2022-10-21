/** @file Token.cpp
 @author Anthony Campos
 @date 12/07/2021
 This is implementation file implements a  data structure known as a
	Token that holds a TokType and a std::string value */

#include "Token.h"


/**  Token Public Methods */

  /** Token constructors  */
Token::Token(TokType t, std::string v)
	:type_(t), value_(v) {}

/** Accessors */

std::string Token::getValue() const {
	return value_;
} // end getValue


TokType Token::getType() const {
	return type_;
} // end getType

/** mutators */

/** setValue */
bool Token::setValue(std::string value) {

	value_ = value;
	return true;

} // end setValue

/** setType */
bool Token::setType(TokType type) {

	type_ = type;
	return true;

} // end setType