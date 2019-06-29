#include"NodeBET.h"


// Binary Expression Tree functions 

bool NodeBET::isLetter(char c)
{
	std::string list = "1234567890qwertyuiopasdfghjklzxcvbnm+-/*^";

	for (char l : list)
	{
		if (c == l)
			return true;
	}

	return false;

}
char NodeBET::getCloseTerm(char c)
{
	if (c == ')') return '(';
	else if (c == ']') return '[';
	else if (c == '}') return '{';
	else return ' ';
}

bool NodeBET::isBalanced(std::string expression)
{
	//this fucntion checks if we have balance size of open & close parenthesis.
	std::stack<char> stack;

	//travell the expression for parenthesis

	for (char testChar : expression)
	{
		if (!isLetter(testChar))
		{
			if (testChar == '(' || testChar == '[' || testChar == '{')
				stack.push(testChar);
			else if (stack.top() == getCloseTerm(testChar))
				stack.pop();
			else
				return false;
		}
	}

	return stack.empty();
}


bool NodeBET::isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
		return true;

	return false;
}

bool NodeBET::IsOperand(char c)
{
	if (c >= '0' && c <= '9') return true;
	else if (c >= 'a' && c <= 'z') return true;
	else if (c >= 'A' && c <= 'Z') return true;

	return false;
}


// Function to get weight of an operator. An operator with higher weight will have higher precedence. 
int NodeBET::GetOperatorWeight(char op)
{
	int weight = -1;

	if (op == '+' || op == '-') weight = 1;
	//else if (op == '*' || op == '/') weight = 2;
	else if (op == '*') weight = 2;
	else if (op == '/') weight = 3;
	else if (op == '^') weight = 4;

	return weight;
}

// Function to verify whether an operator is right associative or not. 
bool NodeBET::IsRightAssociative(char op)
{
	if (op == '^') return true;

	return false;
}

// Function to perform an operation and return output. 
bool NodeBET::HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	// If operators have equal precedence, return true if they are left associative. 
	// return false, if right associative. 
	// if operator is left-associative, left one should be given priority. 
	if (op1Weight == op2Weight)
	{
		if (IsRightAssociative(op1)) return false;
		else return true;
	}
	return op1Weight > op2Weight ? true : false;
}

//convert infix to postfix
std::string NodeBET::ConvertToPosfix(std::string expression)
{
	//Function to evaluate Postfix expression and return output
	std::stack<char> stack;

	std::string posfixOutput = "";

	for (char c : expression)
	{
		//if empty character, go to next iteration
		if (c == ' ' || c == ',') continue;

		//if openTerm
		else if (c == '(') stack.push(c);

		//if character closingTerm, checks for opening in stack 
		else if (c == ')')
		{
			while (!stack.empty() && stack.top() != '(')
			{
				posfixOutput += stack.top();//if not found, add the top to output
				stack.pop();//clean the top
			}
			//if found clean the top again
			stack.pop();
		}
		else if (isOperator(c))
		{
			while (!stack.empty() && HasHigherPrecedence(stack.top(), c) && stack.top() != '(')
			{
				posfixOutput += stack.top();
				stack.pop();
			}
			stack.push(c);
		}
		else if (IsOperand(c))// in case this is a operand, just add to output
			posfixOutput += c;

	}
	//clean the stack with remains character
	while (!stack.empty())
	{
		posfixOutput += stack.top();
		stack.pop();
	}


	return posfixOutput;
}

//convert postfix to prefix
std::string NodeBET::ConvertToPrefix(std::string postExpression)
{
	std::stack<std::string> stack;
	//travell
	for (char c : postExpression)
	{
		if (isOperator(c))
		{
			//pop 2 operands elements from the stack
			std::string operand1 = stack.top();
			stack.pop();
			std::string operand2 = stack.top();
			stack.pop();

			//concats the operands and add it to output
			std::string tempOutput = c + operand2 + operand1;

			stack.push(tempOutput);
		}
		else //then is operand
			stack.push(std::string(1, c));

	}

	//the top holds the prefix expression
	return stack.top();
}

//most important function
NodeBET* NodeBET::ConstructTree(std::string postfix)
{
	std::stack<NodeBET*> stack;

	NodeBET* t1(nullptr); NodeBET* t2(nullptr);
	NodeBET* output(nullptr);

	//traverse
	for (char c : postfix)
	{
		if (!isOperator(c))
		{
			NodeBET* newNode = new NodeBET(c);
			stack.push(newNode);
		}
		else //operator
		{
			NodeBET* newNode = new NodeBET(c);
			//pop 2 elements on top of stack
			t1 = stack.top();
			stack.pop();
			t2 = stack.top();
			stack.pop();

			//make them children
			newNode->right = t1;
			newNode->left = t2;

			//add to stack
			stack.push(newNode);
		}

	}

	//top elemet will be the root of the expression tree
	output = stack.top();
	stack.pop();

	return output;
}

