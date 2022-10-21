/** @file Calculator.h
 @author Anthony Campos
 @date 12/07/2021
 This header class file implements a Symbolic Algebra Calculator that reads in mathematical (algebraic) expressions and represents them in an internal data structure (AST Object) so that they can be manipulated — i.e., simplified, solved, or transformed. */

#pragma once

// included Libraries
#include<vector>
#include<iostream>
#include<stack>
#include<map>

// included Classes
#include "Token.h"
#include "ITokStream.h"
#include "AST.h"

class Calculator{

public:

	/** Calculator constructor*/
	Calculator() = default;

	/** Calculator Public methods*/

	/** Action Methods */

	/** echo starts the calculator and ends/exits the when the char "."is entered.
	takes user input and calls displayExpression to echo the user's input back to the console and the result of the expression
	@post should of evaluated expression inputted that has correct syntax and echo it back to the user with its result
	@parm std::istream [inputStream] the input stream to be tokenized by the ITokStream class*/
	void echo(std::istream& inputStream);
	
private:

	/** private attributes */

	//holds variables and their expressions
	std::map<std::string, AST> variableStore_;

	/** Calculator Private methods*/

	/** tokensToString creates a string representation of the token expression
	@post a string has been created that represents the token vector
	@parm std::vector<Token> [tokens] vector to create a string from
	@returns a string representation of the vector*/
	std::string tokensToString(const std::vector<Token>& tokens) const;

	/** buildExpressionTree creates a AST tree object based of the provided token vector
	@post a AST object is created, a call is made to checkForAssignment in the event the expression has an assignment if true variable and assign token is removed from the vector and stored in variableStore_
	@parm std::vector<Token>& [tokens] expression to use for AST object build
	@returns a AST object based off the provided expression*/
	AST buildAExpressionTree(std::vector<Token>& tokens);

	/** convertToPostfix updates the infix vector to postfix form
	@post vector should now reflect a postfix expression
	@parm std::vector<Token> [curTokenVec] vector to convert*/
	void convertToPostfix(std::vector<Token>& curTokenVec);

	/** precedence determine the precendence of a token that is the type of an operator
	@parm Token [curToken] token to determine the precendence
	@returns a integer value that represents the tokens precendence. 1 is the lowest 3 is the highest*/
	int precendence(const Token& curToken) const;

	/** checkForAssignment checks the expression for an assignment token
	@post if assignment is true string variable is updated to that token.value_
	@parm  std::vector<Token> [tokenChunk] expression to search, std::string [variable] to store the string representation of token.value_
	@return true if the expression contains an assignment and updates variable to that token.value_*/
	bool checkForAssignment(std::vector<Token>& tokenChunk, std::string& variable);

	/** isValidInput checks the expression to confirm it has valid syntax given the assignments input parameters
	@parm std::vector<Token> [expressToCheck]
	@returns true if the vector is a valid expression, false otherwise*/
	bool isValidInput(const std::vector<Token> expressToCheck) const;

	/** displayAndEvaluateExpression displays and evaluates the expression 
	@post displays the vector provided if isValidInput is true, calls tokensToString and displays the expressionVec, then builds a AST tree and calculates the expression and displays the result
	@parm expressionVec*/
	void displayAndEvaluateExpression(std::vector<Token>& expressionVec, int& curExpress);

}; // end of Calculator

