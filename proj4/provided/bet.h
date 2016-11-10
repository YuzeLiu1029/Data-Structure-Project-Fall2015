#ifndef BET_H
#define BET_H

using namespace std;

class BET {
public:
	BET();
	BET(const string postfix);
	BET(const BET &rhs);
	~BET();
	bool buildFromPostfix(const string postfix);
	const BET & operator=(const BET & rhs);
	void printInfixExpression();
	void printPostfixExpression();
	size_t size();
	size_t leaf_nodes();
	bool empty();

private:
	struct BinaryNode {
		string element;
		BinaryNode *left;
		BinaryNode *right;

                 BinaryNode(const string &theElement, BinaryNode *lt = nullptr,BinaryNode *rt = nullptr)
		    :element{theElement},left{lt},right{rt}{}
		 BinaryNode(string &&theElement,BinaryNode *lt = nullptr,BinaryNode *rt = nullptr)
		    :element{move(theElement)},left{lt},right{rt}{}
	};
	BinaryNode *root;
	void printInfixExpression(BinaryNode *n);
	void makeEmpty(BinaryNode* &t);
	BinaryNode * clone(BinaryNode *t) const;
	void printPostfixExpression(BinaryNode *n);
	size_t size(BinaryNode *t);
	size_t leaf_nodes(BinaryNode *t);
};

#include "bet.hpp"

#endif
