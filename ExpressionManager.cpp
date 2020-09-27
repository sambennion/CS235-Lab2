#include "ExpressionManager.h"
using namespace std;
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
	string infix;
	stack<string> operands;
	vector<string> tokens;
	tokens = parseTokens(postfixExpression);
	for(int i = 0; i < tokens.size(); i++){
		if(isOperator(tokens.at(i))){
			if(tokens.empty()){
				return "Error";
			}
			char op = tokens.at(i)[0];
			string left, right, result;
			right = operands.top();
			operands.pop();
			left = operands.top();	
			operands.pop();
			switch (op){
				case '+':
					result = "( " +left + " + " + right + " )";
					break;
				case '-':
					result = "( " +left + " - " + right + " )";
					break;
				case '/':
					result = "( " + left + " / " + right + " )";
					break;
				case '*':
					result = "( " +left + " * " + right + " )";
					break;
				case '%':
					result = "( " + left + " % " + right + " )";
					break;
			}
			operands.push(result);
		}
		else if(isInt(tokens.at(i)[0])){
			operands.push(tokens.at(i));
		}
		else{
			return "Error";
		}
	}
	infix = operands.top();
	return infix;
}

string ExpressionManager::postfixEvaluate(string postfixExpression){
	cout << "postfixEvaluate: " << postfixExpression << endl;
	stack<int> operands;
	vector<string> tokens;
	tokens = parseTokens(postfixExpression);
	stringstream ss;
	for(int i = 0; i < tokens.size(); i++){
		if(isOperator(tokens.at(i))){
			if(tokens.empty()){
				return "Error";
			}
			char op = tokens.at(i)[0];
			int left, right, result;
			right = operands.top();
			operands.pop();
			left = operands.top();
			operands.pop();
			switch (op){
				case '+':
					result = left + right;
					break;
				case '-':
					result = left - right;
					break;
				case '/':
					result = left / right;
					break;
				case '*':
					result = left * right;
					break;
				case '%':
					result = left % right;
					break;
			}
			operands.push(result);
		}
		else if(isInt(tokens.at(i)[0])){
			ss << tokens.at(i);
			int token;
			ss >> token;
			ss.clear();
			operands.push(token);
		}
		else{
			return "Error";
		}
	}
	string finalString;
	for(int i = 0; i < operands.size(); i++){
		string tempString;
		ss << operands.top();
		ss >> finalString;
		ss.clear();
		operands.pop();
	}
	return finalString;
}


string ExpressionManager::infixToPostfix(string infixExpression){
	cout << "infixToPostfix: " << infixExpression << endl;
	string postfix;
	stack<string> operatorStack;
	vector<string> tokens;
	tokens = parseTokens(infixExpression);
	


	string token;
	for(int i = 0; i < tokens.size(); i++){
		token = tokens[i];
		cout << "Token: " << token << endl;
		if(isInt(token[0])){
			postfix += token + " ";
			cout << postfix << endl;
		}
		else if(isOperator(token)){
			cout << "token: " << token << endl;
			process_operator(operatorStack, postfix, token);
			cout << postfix;
		}
		else{
			return "Syntax Error";
		}
	}
	while(!operatorStack.empty()){
		postfix += operatorStack.top() + " ";
		operatorStack.pop();
	}

	return postfix.substr(0, postfix.length() - 1);
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
vector<string> ExpressionManager::parseTokens(string expression)
{
  stringstream ss(expression);
  string token;
  vector<string> tokens;
  while(getline(ss, token, ' '))
  {
    tokens.push_back(token);
  }
  return tokens;
}
bool ExpressionManager::isOperator(string token){
	return token == "+" || token == "-" || token == "/" || token == "%" || token == "*"|| token == "(" || token == ")";
}
bool ExpressionManager::isInt(char token){
	return token == '1' || token == '2' || token == '3' || token == '4' || token == '5' || token == '6' || token == '7' || token == '8' || token == '9' || token == '0';
}

void ExpressionManager::process_operator(stack<string> &opStack, string &postfix, string &op){
	cout << "stack size " << opStack.size() << endl;
	if(!opStack.empty()){

	}
	if(opStack.empty() || isLeftParinth(opStack.top()[0]) || isLeftParinth(op[0])){
			opStack.push(op);
			return;
	}
	
	else if(isRightParinth(op[0])){
		while(!isLeftParinth(opStack.top()[0])){
			postfix += opStack.top() + " ";
			opStack.pop();
			if(opStack.empty()){
				return ;
			}
		}
		opStack.pop();
		return;
	}
	else{
		while(!opStack.empty() && hasPrecedence(op, opStack.top())){
			
			postfix += opStack.top() + " ";
			cout << postfix << endl;
			opStack.pop();
			

		}
		opStack.push(op);
		return;
	}
	
}
//test

bool ExpressionManager::hasPrecedence(string op, string topStackOp){
	int opPrecedence = 0;
	int topStackOpPrecedence = 0;
	if(op == "*" || op == "/" || op == "%"){
		opPrecedence = 2;
	}
	else if(op == "+" || op == "-"){
		opPrecedence = 1;
	}
	if(topStackOp == "*" || topStackOp == "/" || topStackOp == "%"){
		topStackOpPrecedence = 2;
	}
	else if(topStackOp == "+" || topStackOp == "-"){
		topStackOpPrecedence = 1;
	}
	return opPrecedence <= topStackOpPrecedence;
}
