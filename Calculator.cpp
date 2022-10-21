/** @file Calculator.cpp
 @author Anthony Campos
 @date 12/07/2021
 This implementation file implements a Symbolic Algebra Calculator that reads in mathematical (algebraic) expressions and represents them in an internal data structure (AST Object) so that they can be manipulated — i.e., simplified, solved, or transformed. */

#include"Calculator.h"


/** Calculator Public methods*/

/** echo */
void Calculator::echo(std::istream& inputStream) {
	
	ITokStream input(inputStream);
	// Token to insert char into
	Token inputToken;

	int curExpress = 0;

	do {
		// create vector for expression
		std::vector<Token> expressionVec{};
		// insert char into token
		input >> inputToken;

		// if token value is not "." or a newline "\n"
		if (inputToken.getType() != TokType::end && inputToken.getType() != TokType::newline) {

			// if token value is not "." or a newline "\n" 
			while (inputToken.getType() != TokType::newline && inputToken.getType() != TokType::end) {

				// store usable token in vector
				expressionVec.push_back(inputToken);

				//get another token
				input >> inputToken;

			} // end while

			displayAndEvaluateExpression(expressionVec, curExpress);
		} // end if

	} while (inputToken.getType() != TokType::end); // end do


} // end of echo

/** Calculator Private methods*/

/** tokensToString */
std::string Calculator::tokensToString(const std::vector<Token>& tokens) const {

	std::string tokenString = "";
	for (size_t i = 0; i < tokens.size(); ++i) {

		tokenString += tokens[i].getValue();

		if (i != tokens.size() - 1) {
			tokenString += " ";
		} // end if

	} // end if

	return tokenString;
} // end of tokensToString

/** buildExpressionTrees */
AST Calculator::buildAExpressionTree(std::vector<Token>& tokens) {

	// if true tokens will be modified to remove variable
	// and store the variable & expression in variableStorage_
	std::string variable = "";
	AST variableTree;

	if (checkForAssignment(tokens, variable)) {
		variableTree.build(tokens);

		// check if variable is already stored
		std::map<std::string, AST>::iterator it;
		it = variableStore_.find(variable);
		if (it != variableStore_.end()) {
			//variable is present, update variables expression
			variableStore_.erase(it);
			variableStore_.insert(std::pair<std::string, AST>(variable, variableTree));
		}
		else {
			variableStore_.insert(std::pair<std::string, AST>(variable, variableTree));
		} // end if

	}
	else {
		variableTree.build(tokens);
	} // end if
	variable = "";

	return variableTree;

} // end of buildAExpressionTree

/** convertToPostfix */
void Calculator::convertToPostfix(std::vector<Token>& curTokenVec) {

	std::stack<Token> tokenOpStack;
	std::vector<Token> tempVec;

	if (!curTokenVec.empty()) {

		for (auto curtoken : curTokenVec) {

			if (curtoken.getType() == TokType::number || curtoken.getType() == TokType::variable || curtoken.getType() == TokType::assign) {
				// Append operand to end of postfix expression - step 1
				tempVec.push_back(curtoken);

			}
			else if (curtoken.getType() == TokType::lparen) {
				// save '(' on stack - step 2
				tokenOpStack.push(curtoken);
			}
			else if (curtoken.getType() == TokType::addminusop || curtoken.getType() == TokType::muldivop || curtoken.getType() == TokType::powop) {

				// process stack operators of greater precence - step 3
				while (!tokenOpStack.empty() && tokenOpStack.top().getType() != TokType::lparen && precendence(curtoken) <= precendence(tokenOpStack.top())) {

					tempVec.push_back(tokenOpStack.top());
					tokenOpStack.pop();

				} // end while

				// save the operator
				tokenOpStack.push(curtoken);

			}
			else if (curtoken.getType() == TokType::rparen) {

				// pop stack until matching '(' - step 4
				while (tokenOpStack.top().getType() != TokType::lparen) {

					tempVec.push_back(tokenOpStack.top());
					tokenOpStack.pop();

				} // end while
				// remove the open parenthesis
				tokenOpStack.pop();

			}
			else {
				// Toktype unknown
				// do nothing

			} // end if 

		} // end for

		while (!tokenOpStack.empty()) {

			tempVec.push_back(tokenOpStack.top());

			tokenOpStack.pop();
		} // end while

		// add end token

		curTokenVec.clear();

		for (auto token : tempVec) {

			curTokenVec.push_back(token);

		} // end for

	} // end if


} // end of convertToPostfix

 /** precedence */
int Calculator::precendence(const Token& curToken) const {
	// highest precendent is 3, lowest 1
	int rank = 0;

	switch (curToken.getType()) {
		case TokType::powop:
			rank = 3;
			break;
		case TokType::muldivop:
			rank = 2;
			break;
		case TokType::addminusop:
			rank = 1;
			break;
	} // end switch

	return rank; 

} // end precendence

/** checkForAssignment */
bool Calculator::checkForAssignment(std::vector<Token>& tokenChunk, std::string& variable) {
	
	// need to check if there is an assignment operator 

	//std::string variable = "";
	decltype(tokenChunk.size()) searchIndex = 0;
	bool assignFound = false;

	while (!assignFound && searchIndex < tokenChunk.size()) {

		if (tokenChunk[searchIndex].getType() == TokType::assign) {

			assignFound = true;
			variable = tokenChunk[0].getValue();
			// if we find assignment update vector to remove variable & assign token
			// erase the first 2 tokens
			tokenChunk.erase(tokenChunk.begin(), tokenChunk.begin() + 2);
		}
		else {
			++searchIndex;
		} // end if

	} // end while

	return assignFound;

} // end checkForAssignment

/** isValidInput */
bool Calculator::isValidInput(const std::vector<Token> expressToCheck) const {

	bool valid = true;
	std::stack<Token> examineStack;

	// do need to compare last token to stack
	for (size_t i = 0; i < expressToCheck.size() && valid; ++i) {
		
		TokType rhsType = expressToCheck[i].getType();
		
		//unkown token provided
		if (rhsType == TokType::unknown) {
			valid = false;
		} // end if

		if (i == 0) {
			
			if (rhsType == TokType::addminusop || rhsType == TokType::muldivop || rhsType == TokType::powop || rhsType == TokType::assign ) {
				valid = false;
			} // end if

		} // end if


		if (examineStack.empty() && rhsType == TokType::rparen) {
			valid = false;
		} // end if

		if (!examineStack.empty()) {

			TokType lhsType = examineStack.top().getType();

			if (rhsType == TokType::assign) {

				if (i != 1) {
					
					valid = false;
				}
				else {
					
					if (lhsType != TokType::variable) {
						valid = false;
					} // end if

				} // end if
				
			}
			else if (lhsType == rhsType && rhsType != TokType::lparen && rhsType != TokType::rparen) {
				// check for same type except for "(( or ))"
				valid = false;
			}
			else if (lhsType == TokType::powop) {

				if (rhsType != TokType::number) {
					valid = false;
				} // end if
			}
			else if (examineStack.top().getValue() == "/"){

				if (expressToCheck[i].getValue() == "0") {
					valid = false;
				} // end if
		   }
			else if (rhsType == TokType::rparen) {
				
				// remove ")"
				//examineStack.pop();

				// empty () provided
				if (examineStack.top().getType() == TokType::lparen) {

					valid = false;
				} // end if

				// if empty after, there was no "(" 
				if (!examineStack.empty()) {
					
					while (!examineStack.empty() && examineStack.top().getType() != TokType::lparen) {

						if (examineStack.top().getType() != TokType::lparen) {

							if (!examineStack.empty()) {
								examineStack.pop();
							} // end if

						} // end if

					} // end while

					// if the top is a "(" we found the match char, pop it from the stack
					if (!examineStack.empty() && examineStack.top().getType() == TokType::lparen) {
						examineStack.pop();
					} 
					else {
						valid = false;
					}// end if
				}
				else {
					valid = false;

				} // end if

			} // end if

		} // end if

		// push current token onto stack
		// don't push ")" onto the stack
		if (expressToCheck[i].getType() != TokType::rparen) {
			examineStack.push(expressToCheck[i]);
		} // end if

	} // end for

	// pop from stack to see if their is a left over "("
	for (size_t i = examineStack.size(); !examineStack.empty(); --i) {
		
		if (examineStack.top().getType() == TokType::lparen) {
			valid = false;
		} // end if

		examineStack.pop();

	}// end for

	return valid;

} // end of isValidInput

/** displayAndEvaluateExpression */
void Calculator::displayAndEvaluateExpression(std::vector<Token>& expressionVec, int& curExpress) {

	// check for errors in syntax
	if (isValidInput(expressionVec)) {

		// first display input un altered 
		std::cout << "in  [" << (++curExpress) << "]: " << tokensToString(expressionVec) << std::endl;

		// now convert tokens vector to postfix form.
		convertToPostfix(expressionVec);

		//build AST tree
		AST expression = buildAExpressionTree(expressionVec);

		//if the expression has a variable simplify

		if (!expression.containsVariable()) {
			std::cout << "out [" << curExpress << "]: " << expression.calculate() << std::endl;
		}
		else {

			//if the expression has a variable simplify
			auto simplifiedExpress = expression.simplify(variableStore_);

			// if the expression still has a variable don't call calc. 
			if (simplifiedExpress.containsVariable()) {

				std::cout << "out [" << curExpress << "]: " << simplifiedExpress.toInfix() << std::endl;
			}
			else {
				std::cout << "out [" << curExpress << "]: " << simplifiedExpress.calculate() << std::endl;
			} // end if

		} // end if
	}
	else {
		std::cout << "Syntax Error, Expression Skipped" << std::endl;
	} // end if


} // end of displayAndEvaluateExpression
