/** @file AST.cpp
 @author Anthony Campos
 @date 12/07/2021
 This implementation file implements a Abstract Syntax Tree 
   that represents a postfix math expression */

#include "AST.h"


/** AST Class  */

/** AST Class public methods */

/** AST Constructors*/

/** AST Default Constructor*/
AST::AST()
	:root_(nullptr) {
} // end default constructor

/** AST Constructor*/
AST::AST(std::vector<Token>& postfixExpr)
:root_(nullptr){

	// call build method
	build(postfixExpr);

} // end constructor


/** AST Copy Constructor*/
AST::AST(const AST& sourceTree) {
	// call helper method copyTree
	root_ = copyTree(sourceTree.root_);

} // end copy constructor


/*AST overloaded assigment operator*/
AST& AST::operator=(const AST& ast) {

	//self-assignment gaurd
	if (this == &ast) {
		return *this;
	} // end if

	// do copy
	clearTree(root_);
	root_ = copyTree(ast.root_);
	// return the existing object so we can chain this operator
	return *this;

} // end

/** AST copy destructor*/
AST::~AST() {
	// call helper method clearTree
	clearTree(root_);

} // end of destructor

/** toInfix */
std::string AST::toInfix() const {
	//store string object
	std::string str;

	//call toInFixHelper
	toInfixHelper(root_, str);

	return str; // return string created

} // end of toInfix

/** toPostfix() */
std::string AST::toPostfix() const {
	//store string object
	std::string str;

	//call toPostfixHelper
	toPostfixHelper(root_, str);

	return str; // return string created
} // end toPostfix

/** calculate */
std::string AST::calculate() const {
	// string to store answer
	std::string answer = "";
	std::stack<Token> answerStack;
	calculateHelper(root_, answerStack);
	
	// safe guard
	if (!answerStack.empty()) {
		// answer should be only element in stack
		answer = answerStack.top().getValue();
	} // end if
	
	return answer; // return answer

} // end calculate

/** containsVariable */
bool AST::containsVariable() const {
	
	// calls helper method
	return containsVariable(root_);

} // end of containsVariable

/** AST mutators*/

/** build */
bool AST::build(const std::vector<Token>& tokensToAdd) {

	// base case
	if (tokensToAdd.empty()) {
		return false;
	} // end if

	// create an empty stack to store tree pointers
	std::stack<Node*> nodeStack;

	for (auto token : tokensToAdd) {

		// if the current token is an operator
		if (isOperator(token.getType())) {

			Node* rightPtr = nodeStack.top();
			nodeStack.pop();

			Node* leftPtr = nodeStack.top();
			nodeStack.pop();

			// construct a new binary tree whose root is the operator and whose
			// left and right children point to `y` and `x`, respectively
			Node* newNodePtr = new Node(token);

			newNodePtr->right_ = rightPtr;
			rightPtr = nullptr;

			newNodePtr->left_ = leftPtr;
			leftPtr = nullptr;

			// push the current node onto the stack
			nodeStack.push(newNodePtr);
			newNodePtr = nullptr;

		}
		else {
			// if the current token is an operand, create a new binary tree node
			// whose root is the operand and push it into the stack
			nodeStack.push(new Node(token));

		} // end if

	} // end for

	root_ = nodeStack.top();

	return true;

} // end build

/** simplify */
AST AST::simplify(std::map<std::string, AST>& variableStore) const {

	// search AST
	// if varible found in variable store
	// replace variable with expression stored in variable
	AST newTree = *this;
	// call helper method
	simplifyHelper(newTree.root_, variableStore);
	return newTree; // return new tree

} // end of simplify

/** AST Class private methods */

/** getHeightHelper */
int AST::getHeightHelper(const Node* subTreePtr) const {

	// base case
	if (subTreePtr == nullptr) {
		return 0;
	}
	else {
		return 1 + std::max(getHeightHelper(subTreePtr->left_), getHeightHelper(subTreePtr->right_));
	} // end if

} // end of getHeightHelper

/** isOperator */
bool AST::isOperator(const TokType& type) const {

	return (type == TokType::addminusop || type == TokType::muldivop || type == TokType::powop);

} // end for isOperator

/** copyTree */



AST::Node* AST::copyTree(const Node* oldTreePtr) const {

	//initilaize new node for the new tree. 
	Node* newTreePtr = (oldTreePtr != nullptr) ? new Node(oldTreePtr->tok_) : nullptr;
	// copy tree nodes during a preorder traversal

	if (oldTreePtr != nullptr) {
		
		// copy node
		newTreePtr->left_ = copyTree(oldTreePtr->left_);
		newTreePtr->right_ = copyTree(oldTreePtr->right_);

	} // end if
	// else tree is empty (newTreePtr is nullptr)

	return newTreePtr;

} // end copyTree

/** clearTree */
void AST::clearTree(Node*& subTreePtr) {

	// made it passed by reference

	if (subTreePtr != nullptr) {
		
		clearTree(subTreePtr->left_);
		clearTree(subTreePtr->right_);
		
		// release memory
		delete subTreePtr;
		subTreePtr = nullptr;

	} // end if

} // end clearTree

/** doMath */
std::string AST::doMath(const Token& tokenOptr, const Token& leftOperand, const Token& rightOperand) const {

	// stores result of the evaluation 
	int result = 0;
	// converts the provided string objects to int
	int leftOp = std::stoi(leftOperand.getValue());
	int rightOp = std::stoi(rightOperand.getValue());

	// switch to determine operation to use. 
	switch (tokenOptr.getType())
	{
	case TokType::addminusop:
		//do + or -
		if (tokenOptr.getValue() != "-") {
			result += (leftOp + rightOp);
		}
		else {
			result += (leftOp - rightOp);
		} // end if
		break;
	case TokType::muldivop:
		//do * or /
		if (tokenOptr.getValue() != "/") {
			result += (leftOp * rightOp);
		}
		else {
			result += (leftOp / rightOp);
		}// end if
		break;
	case TokType::powop:
		// do ^ 
		result += static_cast<int>(pow(leftOp, rightOp));
	default:
		break;
	} // end switch

	// convert int back to string and return
	return std::to_string(result);
} // end of doMath

/** containsVariable */
bool AST::containsVariable(const Node* treePtr) const {

	if (treePtr == nullptr) {
		return false;
	}
	else if (treePtr->tok_.getType() == TokType::variable) {
		return true;
	} // search left child
	else if (containsVariable(treePtr->left_)) {
		return true;
	}
	else { // search right child
		return containsVariable(treePtr->right_);
	} // end if

} // end of containsVariable 

/** replace */
void AST::replace(Node*& subTreePtr, const Node* insertPtr) const {

	// if node exisit replace values in node
	if (subTreePtr != nullptr) {
		subTreePtr->tok_.setValue(insertPtr->tok_.getValue());
		subTreePtr->tok_.setType(insertPtr->tok_.getType());
	} // end if

	// if no node create a node to insert into tree
	if (subTreePtr == nullptr) {
		Node* newNode = new Node(insertPtr->tok_);
		subTreePtr = newNode;

	} // end if

	// replace left node 
	if (insertPtr != nullptr && insertPtr->left_ != nullptr) {
		replace(subTreePtr->left_, insertPtr->left_);
	}
	// replace right node
	if (insertPtr != nullptr && insertPtr->right_ != nullptr) {
		replace(subTreePtr->right_, insertPtr->right_);
	} // end if

} // end replace

/** toInfixHelper */
void AST::toInfixHelper(const Node* treePtr, std::string& str) const {

	if (treePtr != nullptr) {

		TokType curTokenType = treePtr->tok_.getType();
		//if token is a operator insert '('

		if (isOperator(curTokenType) && curTokenType != TokType::powop && getHeightHelper(treePtr) != getHeightHelper(root_)) {

			str += "( ";

		} // end if

		toInfixHelper(treePtr->left_, str);

		str += treePtr->tok_.getValue() + " ";
		
		toInfixHelper(treePtr->right_, str);
		//if token is a operator insert ')'
		if (isOperator(curTokenType) && curTokenType != TokType::powop && getHeightHelper(treePtr) != getHeightHelper(root_)) {
			str += ") ";

		} // end if

	} // end if

} // end of toInfixHelper

/** toPostfixHelper */
void AST::toPostfixHelper(const Node* treePtr, std::string& str) const {
	
	if (treePtr != nullptr) {

		toPostfixHelper(treePtr->left_, str);
		toPostfixHelper(treePtr->right_, str);

		str += treePtr->tok_.getValue();

		if (getHeightHelper(treePtr) != 0) {

			str += " ";

		} // end if

	} // end if

} // end of toPostfixHelper


/** calculateHelper */
void AST::calculateHelper(const Node* treePtr, std::stack<Token>& tokenStack) const {

	if (treePtr != nullptr) {

		calculateHelper(treePtr->left_, tokenStack);
		calculateHelper(treePtr->right_, tokenStack);
		// if current node is an operand, pop off operands on the stack for use
		if (isOperator(treePtr->tok_.getType())) {

			// get left and right operands
			Token leftOp = tokenStack.top();
			tokenStack.pop();

			Token rightOp = tokenStack.top();
			tokenStack.pop();
									
			// create a node for our answer
			Token answerToken;
			answerToken.setValue(doMath(treePtr->tok_, rightOp, leftOp));

			// push the answer token onto the stack
			tokenStack.push(answerToken);
			
		}
		else {
			// if the current token is an operand
			tokenStack.push(treePtr->tok_);
		} // end if
		
	} // end if
	
} // end of calculateHelper

/** simplifyHelper */
void AST::simplifyHelper(Node*& treePtr, const std::map<std::string, AST>& variableStore) const{
	// create iterator to search variableStore
	std::map<std::string, AST>::const_iterator it;

	// base case
	if (treePtr == nullptr) {	
		return;
	} // end if

	if (treePtr->tok_.getType() == TokType::variable) {
		
		// search variable store for the given variable in the current expression
		it = variableStore.find(treePtr->tok_.getValue());

		// if iterator does not equal end, variable found
		if (it != variableStore.end()) {
			// replace the variable with its expression
			replace(treePtr, it->second.root_);
		} // end if
	} // end if

	// search down left child
	if (treePtr != nullptr && treePtr->left_ != nullptr) {
		simplifyHelper(treePtr->left_, variableStore);
	} // end if

	// search down right child
	if(treePtr != nullptr && treePtr->right_ != nullptr){ // search right tree
		simplifyHelper(treePtr->right_, variableStore);
	} // end if

} // end of simplifyHelper


/** Node Class  */

/** Node Class public methods */

/** Node Constructor */
AST::Node::Node(Token t) 
:tok_(t), left_(nullptr), right_(nullptr){
} // end of Node Constructor

/** Node Class private methods */