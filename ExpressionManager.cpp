#include "ExpressionManager.h"

bool ExpressionManager::isBalanced(string expression){
	cout << "isBalanced: " << expression << endl;
	
	bool balanced = true;
	stack<char> stack;

	for(int i = 0; i < expression.length() && balanced; i++){
		if(isLeftParinth(expression.at(i))){
			stack.push(expression.at(i));
		}
		else if(isRightParinth(expression.at(i))){
			if(stack.empty()){
				balanced = false;
			}
			else if(isMatchedParinth(stack.top(), expression.at(i))){
				stack.pop();
			}
			else{
				balanced = false;
			}
		}
	}
	if(!(stack.empty() && balanced)){
		balanced = false;
	}
	return balanced;

}

string ExpressionManager::postfixToInfix(string postfixExpression){
	cout << "postfixToInfix: " << postfixExpression << endl;
	
	return "REPLACE";
}

string ExpressionManager::postfixEvaluate(string postfixExpression){
	cout << "postfixEvaluate: " << postfixExpression << endl;
	return "REPLACE";
}

string ExpressionManager::infixToPostfix(string infixExpression){
	cout << "infixToPostfix: " << infixExpression << endl;
	return "REPLACE";
}
//Helper Functions
bool ExpressionManager::isMatchedParinth(char left, char right){
	bool pair = false;
	if(left == '(' && right ==')'){
		pair = true;
	}
	else if(left == '{' && right =='}'){
		pair = true;
	}
	else if(left == '[' && right ==']'){
		pair = true;
	}
	return pair;
}
bool ExpressionManager::isLeftParinth(char parinth){
	bool isLeft = false;
	if(parinth == '(' || parinth == '{' || parinth == '['){
		isLeft = true;
	}
	return isLeft;
}
bool ExpressionManager::isRightParinth(char parinth){
	bool isRight = false;
	if(parinth == ')' || parinth == '}' || parinth == ']'){
		isRight = true;
	}
	return isRight;
}