/** @file AST.h
 @author Anthony Campos
 @date 12/07/2021
 This header class file implements a Abstract Syntax Tree 
 that represents a postfix math expression */

#pragma once

// included classes
#include "Token.h"

// included libraries
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <map>


/** Abstract Syntax Tree Class*/
class AST {

public:


   /** AST constructors*/
   AST();

   AST(std::vector<Token>& postfixExpr);

   /** AST copy constructor*/
   AST(const AST& sourceTreePtr);

   /** AST destructor*/
   ~AST();

   /** AST public methods*/

   /*AST overloaded assigment operator
   @post left hand AST object equals the right hand AST object
   @param AST [ast] object to equal
   @return AST oject is now equal to right hand AST boject*/
   AST& operator=(const AST& ast);

   /** toInfix builds a string object in infix form of the AST object 
   @return a string in infix form per the tokens in the AST object*/
   std::string toInfix() const;

   /** toPostfix builds a string object in postfix form of the AST object
   @return a string in postfix form per the tokens in the AST object*/
   std::string toPostfix() const;

   /** calculate calculates the result of the expression stored in the AST
   @return the calculated result of the AST object as a string*/
   std::string calculate() const;

   /** containsVariable
   @return true if the AST object containes a token that holds a variable*/
   bool containsVariable() const;

   /** AST mutators*/

   /** build builds out the tree struture of the AST object pre the provided vector
   @post if successful, an AST object is filled based off the Tokens in
   tokensToAdd
   @parm std::vector<Token> [tokensToAdd] the vector to fill the tree with
   @return true if successful*/
   bool build(const std::vector<Token>& tokensToAdd);

   /** simplify the expression by replacing variables with their assigned expression if any
   @post creates a new AST object that is a simplified
   @parm std::map<std::string, AST>& [variableStore] holds variables and their assigned expressions
   @return a new AST object that is a simplifed version of the current AST object*/
   AST simplify(std::map<std::string, AST>& variableStore) const;


private:

   /** Node Struct */
   struct Node {

      /** Node Constructor */
      Node(Token t);

      /** Node Attributes  */

      // holds the input toke
      Token tok_;

      // left child pointer for tree struture
      Node* left_;

      // right child pointer for tree structure
      Node* right_;

   };

   /** Abstract Syntax Tree Attributes*/

   // pointer root of the tree struture
   Node* root_;

   /** AST public private*/

   /** getHeightHelper returns the hight of the tree
   @parm Node*[subTreePtr] the starting node to check
   @returns the hight of the tree as an interger value*/
   int getHeightHelper(const Node* subTreePtr) const;

   /** isOperator determine if the token's type is an 
   operator per its TokType value
   @parm TokType [token] the given's token's type
   @return true if the provided TopType is an Operator*/
   bool isOperator(const TokType& token) const;

   /** copyTree copies a tree provided another tree's root
   @post provided tree copied and pointer to the copy returned
   @parm Node* [oldTreePtr] tree's root to copy
   @return a copy of the provided tree*/
   Node* copyTree(const Node* oldTreePtr) const;

   /** copyTree destroys the tree object
   @post all memory for the AST object is deallocated
   @parm Node* [subTreePtr] pointer to the root of the tree*/
   void clearTree(Node*& subTreePtr);

   /** doMath does the math for two operands and one operator
   @post calculated the result of the provided operands and operator
   @param Token[tokenOptr] the operator Token[leftOperand] left operand Token[rightOperand] right operand
   @return a string representation of calculated math expression*/
   std::string doMath(const Token& tokenOptr, const Token& leftOperand, const Token& rightOperand) const;
   
   /** containsVariable searchs the tree for a variable token
   @parm Node* [treePtr] root of the tree, starting point
   @return true if the tree contains a variable, false otherwise*/
   bool containsVariable(const Node* treePtr) const;

   /** replace recrusively inserts a expression tree at a specific variable location, replacing that variable with its expression if any
   @post variable stored at the specific node location will be replaced with its assigned expression
   @parm Node* [subTreePtr] root of the tree, starting point, Node* [insertPtr] root of the tree to insert  */
   void replace(Node*& subTreePtr, const Node* insertPtr) const;

   /** toInfixHelper recuisve methods that does the work for the toInfix method
   @post constructs a string in infix form by traversing the tree
   @parm Node* [treePtr] tree root pointer, string [str] to store the constructed string in*/
   void toInfixHelper(const Node* treePtr, std::string& str) const;

   /** toPostfixHelper recuisve methods that does the work for the toPostfix method
   @post constructs a string in infix form by traversing the tree
   @parm Node* [treePtr] tree root pointer, string [str] to store the constructed string in*/
   void toPostfixHelper(const Node* treePtr, std::string& str) const;

   /** calculateHelper recursive traversal of the tree in postfix order calculated the result of the expression tree
   @post calculates the result of the expression tree and calls doMath to do the operation, and stores the result on the top of the tokenStack
   @param Node*[treePtr] root of the tree std::stack<Token>[tokenStack] result stack */
   void calculateHelper(const Node* treePtr, std::stack<Token>& tokenStack) const;

   /** simplifyHelper recursive method searches the tree for variables that have assigned expressions, if one is found replace is called to insert a that variables expression/replace it
   @post the provided tree has been simplifed by replaces variables with their expressions
   @param Node*[treePtr] root of the tree, starting point, std::map<std::string, AST> [variableStore] variable expression storage to reference*/
   void simplifyHelper(Node*& treePtr, const std::map<std::string, AST>& variableStore) const;

}; // end of AST