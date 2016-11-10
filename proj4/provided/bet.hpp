#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stack>
#include <ctype.h>
#include "bet.h"

using namespace std;

BET::BET(){
	root = nullptr;
}

BET::BET(const string postfix): root{nullptr}{
	
	//if(!empty())
		//makeEmpty(root);
	//root = nullptr;
	if(!buildFromPostfix(postfix)){
		cout << "ERROR OCCURRED!" << endl;
	}
}

BET::BET(const BET &rhs){
	*this = rhs;	
}

BET::~BET(){
	makeEmpty(root);
}

bool BET::buildFromPostfix(const string postfix){
	stringstream ss(postfix);
	stringstream ss2;
	string tempString;
	stack<BinaryNode*> oStack;
	BinaryNode *temp;

	while(ss >> tempString){
		if(tempString == "+" || tempString == "-" || tempString == "*" || tempString == "/"){
			temp = new BinaryNode(tempString);
			//temp->element = tempString;
			temp->right = oStack.top();
			oStack.pop();
			temp->left = oStack.top();
			oStack.pop();

			oStack.push(temp);
		} else {
		
			temp = new BinaryNode(tempString);
			//temp->element = tempString;
			//temp->left = new BinaryNode{nullptr, nullptr,nullptr};
			// temp->right =new Bnarynode{nullptr,nullptr,nullptr};
			oStack.push(temp);
		}

	}

	
	root = oStack.top();

	return true;
}

const BET & BET::operator=(const BET & rhs){
	root = clone(rhs.root);
	return *this;	
}

void BET::printInfixExpression(){
	printInfixExpression(root);
	cout << endl;
}

void BET::printPostfixExpression(){
	printPostfixExpression(root);
	cout << endl;
}

size_t BET::size(){
        //if(root == NULL)
	 //return 0;
	//else{
	  return size(root);
//	}
}

size_t BET::leaf_nodes(){
	//if(root == NULL)
	 //return 0;
	//else{
	return leaf_nodes(root);}
//}

bool BET::empty(){
	//if(size() == 0)
	if(root == NULL){
		return true;}
	return false;
}

void BET::makeEmpty(BinaryNode* &t){
	if(t != nullptr){
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
}

BET::BinaryNode * BET::clone(BinaryNode *t) const{
	if(t == NULL){
        	return NULL;
    	}
	else
	 return new BinaryNode{t->element,clone(t->left),clone(t->right)};
    	//BinaryNode newNode;
  
        //string element(t->element);
        //newNode.element = element;
    	
 
   	//newNode.left = clone(t->left);
    	//newNode.right = clone(t->right);
	//BinaryNode * returnNode = new BinaryNode(newNode);
    	//return returnNode;
}

void BET::printInfixExpression(BinaryNode *n){
	if(n!=NULL){
		if(n->element == "+" || n->element == "-" || n->element == "*" || n->element == "/")
			if(n != root)
				cout << " ( ";
		printInfixExpression(n->left);
		cout << " " << n->element << " ";
		printInfixExpression(n->right);
		if(n->element == "+" || n->element == "-" || n->element == "*" || n->element == "/")
			if(n != root)
				cout << " ) ";
	}
}

void BET::printPostfixExpression(BinaryNode *n){
	if(n!=NULL){
		printPostfixExpression(n->left);
		printPostfixExpression(n->right);
		cout << n->element << " ";
	}
}

size_t BET::size(BinaryNode *t){
	if(t==NULL)
	  return 0;
	else{
	  	return( size(t->left) + size(t->right) + 1 );}
}

size_t BET::leaf_nodes(BinaryNode *t){
       if(t==NULL)
         return 0;
       else if ((t -> left == NULL) && (t->right == NULL)){
         return 1;}
       else{
                return( leaf_nodes(t->left) + leaf_nodes(t->right));}
}

