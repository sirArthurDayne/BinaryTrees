#pragma once
#include<iostream>
#include<string>
#include<stack>
////////////////////////////////BINARY EXPRESSION TREE/////////////////////////////////
//typedef NodeBET* nodebetptr;
struct NodeBET
{
public:
	char letter;
	NodeBET* right;
	NodeBET* left;

	NodeBET(char data) {
		letter = data;
		right = left = nullptr;
	}

	bool isLetter(char c);
	char getCloseTerm(char c);
	bool isBalanced(std::string expression);
	bool isOperator(char c);
	bool IsOperand(char c);
	int GetOperatorWeight(char op);
	bool IsRightAssociative(char op);
	bool HasHigherPrecedence(char op1, char op2);
	std::string ConvertToPosfix(std::string expression);
	std::string ConvertToPrefix(std::string postExpression);
	NodeBET* ConstructTree(std::string postfix);

};

