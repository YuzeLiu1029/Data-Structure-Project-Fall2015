//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////COP4530 Proj3/////////////////////////////////////////////////////////////////
///////////////////////////////Yuze Liu///////////////////////////////////////////////////////////////////////
//////////////////////////////Thank you for grading///////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include <cctype>
#include "stack.h"

using namespace std;
using namespace cop4530;

int operatorRank(string oper){
	
	if(oper == "*" || oper == "/")
		return 1;
	else if ( oper == "+" || oper == "-")
		return 2;
        else if(oper == "(")
		return 3;
	else
	  return 0;
}

string eval(Stack<string> & storeStack){
	stringstream ss;
	Stack<float> evalStack;
	ss << storeStack;

	string strTemp;
	stringstream returnSS;
	string returnStr;


	while(ss >> strTemp){
		stringstream ss2(strTemp);
		float floatTemp;
		if(ss2 >> floatTemp){
			evalStack.push(floatTemp);
		} else if(strTemp.length() > 1){
			returnSS << storeStack;
			getline(returnSS, returnStr);
			return returnStr;
		} else if(isalpha(strTemp[0])){
				returnSS << storeStack;
				getline(returnSS, returnStr);
				return returnStr;
		} else if(strTemp == "+" || strTemp == "-" || strTemp == "*" || strTemp == "/"){
			if(evalStack.size() < 2)
				return "\nError: Missing operand in postfix string. Unable to evaluate postfix string!";
			float rhs = evalStack.top();
			evalStack.pop();
			float lhs = evalStack.top();
			evalStack.pop();

			switch(strTemp[0]){
				case '+':
					evalStack.push(lhs+rhs);
					break;
				case '-':
					evalStack.push(lhs-rhs);
					break;
				case '/':
					evalStack.push(lhs/rhs);
					break;
				case '*':
					evalStack.push(lhs*rhs);
					break;
			}
		} else
			cout << "ERROR ENCOUNTERED!" << endl;
	}

	returnSS << evalStack;
	getline(returnSS, returnStr);		
	return returnStr;
}


void parser(Stack<string> & storeStack, string input){
	Stack<string> opStack;
	stringstream ss(input);
	string temp;

	int paren = 0;
	int isNum = 0;
	int isOp = 0;
	while(ss>>temp){
		if(temp == "+" || temp == "-" || temp == "*" || temp == "/"){
			isOp++;
			while(!opStack.empty() && operatorRank(opStack.top()) <= operatorRank(temp)){
				storeStack.push(opStack.top());
				opStack.pop();
			}
			opStack.push(temp);
		} else if (temp == "("){
			paren++;
			opStack.push(temp);
		} else if (temp == ")"){
			paren--;
			if(!opStack.empty()){
				while(opStack.top() != "("){
					storeStack.push(opStack.top());
					opStack.pop();
				}
			opStack.pop();
			} else {
				cout << "Error: Infix expression: " << input << " has mismatched parens!" << endl;
				return;
			}
		} else {
			storeStack.push(temp);
			isNum++;
		}
	}
	
	while(!opStack.empty()){
		storeStack.push(opStack.top());
		opStack.pop();

	}
	if(isNum == 0){
		cout << "Error: Missing operands in the expression" << endl;
		return;
	} else if(isOp == 0){
		cout << "Error: Missing operators in the expression" << endl;
		return;
	} else if(paren != 0){
		cout << "Error: Infix expression: " << input << "has mismatched parens!" << endl;
		return;
	} else {
		cout << "Postfix expression: " << storeStack << endl;
		cout << "Postfix evaluation: " << storeStack << " = " << eval(storeStack) << endl;
	}		
}

int main(){
	Stack<string> storeStack;
	string input;
	cout << "Enter infix expression (\"exit\" to quit): ";
	while(getline(cin, input)){
		cout << endl;
		if(input == "exit")
			return 0;
		parser(storeStack, input);
		cout << "Enter infix expression (\"exit\" to quit): ";
		storeStack.clear();
	}


	cout << endl;
	return 0;
}

