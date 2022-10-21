/** @file ITokStream.cpp
 @author Anthony Campos
 @date 12/07/2021
 This implementation file implements a tokenizer that tokenizes a
	inputted algebraic expessions into its components */


#include "ITokStream.h"


/** ITokStream Public Methods */


/**  ITokStream constructor */
ITokStream::ITokStream(std::istream& inputStream)
	:is_(inputStream) {
}

/**  ITokStream Public methods */

/** Overloaded operator>> */
ITokStream& ITokStream::operator>>(Token& rhs)
{
	char currChar;
	is_.get(currChar); // set current char

	// if currChar is a white space
	while (currChar == ' ') {
		
		// get next char
		is_.get(currChar);

	} // end while

	// determine Token Type per currChar
	determineTokenType(currChar, rhs);

	if (isalpha(currChar)) {
		currChar = tolower(currChar);
	} // end if

	std::string tokenValue{ currChar };
	//check to see if multi digit number
	if (isdigit(currChar)) {
		
		// look forward to see if next char is a digit
		while (isdigit(is_.peek())) {
			
			is_.get(currChar);
			tokenValue += currChar;

		} // end while

	} // end if

	if (currChar == ':') {

		if (is_.peek() == '=') {
			
			is_.get(currChar);
			tokenValue += currChar;

		}
		else {
			//special case
			// incomplete assignment token provided
			rhs.setType(TokType::unknown);
		}// end if

	} // end if

	// set Token value_
	rhs.setValue(tokenValue);

	return *this;

} // end method

/**  Overloaded bool() */
ITokStream::operator bool() const {
	// check state of stream
	return is_.good();

} // end of operator bool

/**  ITokStream Private methods */

/**  determineTokenType */
void ITokStream::determineTokenType(const char input, Token& curToken) {

	// determine Token type
	if (isdigit(input)) {
		curToken.setType(TokType::number);
	}
	else if (isalpha(input)) {
		curToken.setType(TokType::variable);
	}
	else if (input == '+' || input == '-') {
		curToken.setType(TokType::addminusop);
	}
	else if (input == '*' || input == '/') {
		curToken.setType(TokType::muldivop);
	}
	else if (input == '^') {
		curToken.setType(TokType::powop);
	}
	else if (input == '(') {
		curToken.setType(TokType::lparen);
	}
	else if (input == ')') {
		curToken.setType(TokType::rparen);
	}
	else if (input == ':') {
		curToken.setType(TokType::assign);
	}
	else if (input == '.') { // is end
		curToken.setType(TokType::end);
	} 
	else if(input == '\n') {
		curToken.setType(TokType::newline);
	} 
	else {
		curToken.setType(TokType::unknown);
	} // end if

} // end determineTokenType

