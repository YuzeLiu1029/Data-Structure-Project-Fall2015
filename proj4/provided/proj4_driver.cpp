#include <iostream>
#include <string>
#include "bet.h"

using namespace std;

int main() {
    string postfix;

    
    cout << "Enter the first postfix expression: ";
    getline(cin, postfix);

    
    BET bet1(postfix);
    if (!bet1.empty()) {
    	cout << "Infix expression: ";
    	bet1.printInfixExpression();

	cout << "Postfix expression: ";
	bet1.printPostfixExpression();

	cout << "Number of nodes: ";
	cout << bet1.size() << endl;

	cout << "Number of leaf nodes: ";
	cout << bet1.leaf_nodes() << endl;

    	
    	BET bet2(bet1);
    	cout << "Testing copy constructor: ";
    	bet2.printInfixExpression();

    	
    	BET bet3;
    	bet3 = bet1;
    	cout << "Testing assignment operator: ";
    	bet3.printInfixExpression();
    }

    cout << "Enter a postfix expression (or \"quit\" to quit): ";
    while (getline(cin, postfix)) {
	if (postfix == "quit") {
	    break;
        }
	if (bet1.buildFromPostfix(postfix)) {
	    cout << "Infix expression: ";
	    bet1.printInfixExpression();
	    
	    cout << "Postfix expression: ";
	    bet1.printPostfixExpression();
		
	    cout << "Number of nodes: ";
	    cout << bet1.size() << endl;

	    cout << "Number of leaf nodes: ";
	    cout << bet1.leaf_nodes() << endl;
	}
	cout << "Enter a postfix expression (or \"quit\" to quit): ";
    }
    return 0;
}
