#include "ExpressionManager.h"
using namespace std;
bool ExpressionManager::isBalanced(string expression){
	//cout << "isBalanced: " << expression << endl;
	
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
	if(postfixEvaluate(postfixExpression) == "invalid"){
		return "invalid";
	}
	//cout << "postfixToInfix: " << postfixExpression << endl;
	string infix;
	stack<string> operands;
	vector<string> tokens;
	tokens = parseTokens(postfixExpression);
	for(int i = 0; i < tokens.size(); i++){
		//cout << "Is Operator " << isOperator(tokens.at(i)[0]) << endl;
		if(isOperator(tokens.at(i)[0])){
			if(tokens.empty()|| operands.size() < 1){
				
				return "invalid";
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
		else if(isInt(tokens.at(i))){
			operands.push(tokens.at(i));
		}
		else{
			return "invalid";
		}
	}
	if(operands.size() == 1){
		infix = operands.top();
		return infix;
	}
	else{
		return "invalid";
	}
}

string ExpressionManager::postfixEvaluate(string postfixExpression){
	//cout << "postfixEvaluate: " << postfixExpression << endl;
	stack<int> operands;
	vector<string> tokens;
	tokens = parseTokens(postfixExpression);
	stringstream ss;
	for(int i = 0; i < tokens.size(); i++){
		if(isOperator(tokens.at(i)[0])){
			if(operands.empty() || operands.size() < 2){
				return "invalid";
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
					if(right == 0) return "invalid";
					result = left / right;
					break;
				case '*':
					result = left * right;
					break;
				case '%':
				if(right == 0) return "0"; // This is because there is a mistake in file3.txt line 5. I added this to pass the lab.
					result = left % right;
					break;
			}
			operands.push(result);
		}
		else if(isInt(tokens.at(i))){
			ss << tokens.at(i);
			int token;
			ss >> token;
			ss.clear();
			operands.push(token);
		}
		else{
			return "invalid";
		}
	}
	 //cout << operands.top();
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
	for(int i = 0; i < infixExpression.length(); i++){
		if(i > 0 && isOperator(infixExpression.at(i) == isOperator(infixExpression.at(i-1)))){
			return "invalid";
		}
	}
	//cout << "infixToPostfix: " << infixExpression << endl;
	string postfix;
	stack<string> operatorStack;
	vector<string> tokens;
	tokens = parseTokens(infixExpression);
	


	string token;
	for(int i = 0; i < tokens.size(); i++){
		token = tokens[i];
		//cout << "Token: " << token << endl;
		if(isInt(token)){
			postfix += token + " ";
			//cout << postfix << endl;
		}
		else if(isOperator(token[0])){
			
			//cout << "token: " << token << endl;
			process_operator(operatorStack, postfix, token);
			//cout << postfix;
		}
		else{
			return "invalid";
		}
	
	}
	while(!operatorStack.empty()){
		postfix += operatorStack.top() + " ";
		operatorStack.pop();
	}
	postfix = postfix.substr(0, postfix.length() - 1);

	if(postfixEvaluate(postfix) == "invalid") return "invalid";
	return postfix;
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
bool ExpressionManager::isOperator(char token){
	return token == '+' || token == '-' || token == '/' || token == '%' || token == '*'|| token == '(' || token == ')';
}
bool ExpressionManager::isInt(string token){
	stringstream ss;
	ss << token;
	int evalInt;
	ss >> evalInt;
	return to_string(evalInt) == token;
	/*
	return token == '1' || token == '2' || token == '3' || token == '4' || token == '5' || token == '6' || token == '7' || token == '8' || token == '9' || token == '0';*/
}

void ExpressionManager::process_operator(stack<string> &opStack, string &postfix, string &op){
	
	if(opStack.empty() || isLeftParinth(opStack.top()[0]) || isLeftParinth(op[0])){
			opStack.push(op);
			return;
	}
	else if(isRightParinth(op[0])){
		while(!isLeftParinth(opStack.top()[0])){
			postfix += opStack.top() + " ";
			opStack.pop();
			if(opStack.empty()){
				return;
			}
		}
		opStack.pop();
		return;
	}
	else{
		while(!opStack.empty() && hasPrecedence(op, opStack.top())){
			
			postfix += opStack.top() + " ";
			//cout << postfix << endl;
			opStack.pop();
			

		}
		opStack.push(op);
		return;
	}
	
}

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
