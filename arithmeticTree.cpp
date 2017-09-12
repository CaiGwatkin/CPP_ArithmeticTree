//////////////////////////////////////////////
//	Cai Gwatkin								//
//////////////////////////////////////////////
//	This application prints the contents	//
//	of an arithmetic tree in pre- and		//
//	post-order notation						//
//////////////////////////////////////////////

#include "arithmeticTree.h"


int main(int argc, char** argv)
{
	if (argc != 2) return ErrArguments();

	return ArithmeticTree(argv[1]);
}

// Tree constructor
Tree::Tree(const char newData, Tree *left, Tree *right)
{
	data = newData;
	leftPointer = left;
	rightPointer = right;
}

// stack constructor
Stack::Stack()
{
	listPointer = NULL;
}

// stack destructor
Stack::~Stack()
{
	while (listPointer != NULL)
	{
		Node *temp = listPointer;
		listPointer = listPointer->next;
		delete temp;
	}
}

// adds a Tree pointer to the top of the Stack
void Stack::Push(Tree *t)
{
	Node *temp;
	temp = new Node;
	temp->treePointer = t;
	temp->next = listPointer;
	listPointer = temp;
}

// removes the top Tree pointer from the Stack
void Stack::Pop()
{
	Node *temp;
	temp = listPointer;
	if (listPointer != NULL)
	{
		listPointer = listPointer->next;
		delete temp;
	}
}

// checks if the Stack is empty
bool Stack::IsEmpty()
{
	if (listPointer == NULL) return true;
	return false;
}

// returns the Tree pointer from the top of the Stack
Tree* Stack::Top()
{
	return listPointer->treePointer;
}

// returns error code if there are not enough arguments passed to the program
int ErrArguments()
{
	cout << "Error: need 2 arguments" << endl;
	return 1;
}

// returns error code if the file cannot be opened
int ErrFile(const char *fileName)
{
	cout << "Error: \"" << fileName << "\" cannot be opened" << endl;
	return 2;
}

// adds a digit to the Stack (create new Tree)
void AddDigit(const char digit, Stack &treeCreation)
{
	treeCreation.Push(new Tree(digit, NULL, NULL));
}

// adds an operator to the Stack (create new Tree)
void AddOperator(const char oper, Stack &treeCreation)
{
	// get Tree pointers
	Tree *tree2 = treeCreation.Top();
	treeCreation.Pop();
	Tree *tree1 = treeCreation.Top();
	treeCreation.Pop();
	
	// create new Tree using the operator and Tree pointers
	treeCreation.Push(new Tree(oper, tree1, tree2));
}

// creates Arithmetic Tree from RPN text file
int CreateTree(const char *fileName, Tree *&arithmeticTree)
{
	// open RPN text file
	ifstream inFile(fileName);
	if (!inFile) return ErrFile(fileName);

	// create Stack to use for Tree creation
	Stack treeCreation;

	// itterate through lines of file, adding Nodes to the Stack (creating the Tree)
	while (!inFile.eof())
	{
		string line;
		inFile >> line;

		if (isdigit(line[0])) AddDigit(line[0], treeCreation);
		else if ((line[0] == '+') || (line[0] == '-') || (line[0] == '*') || (line[0] == '/')) AddOperator(line[0], treeCreation);
	}

	// make the Arithmetic Tree root the root of the created Tree
	arithmeticTree = treeCreation.Top();

	return 0;
}

// recursive in-order tree traversal for output
void InOrder(Tree *tree)
{
	if (tree == NULL) return;
	if (tree->Left() != NULL)
	{
		cout << "(";
		InOrder(tree->Left());
	}
	cout << tree->RootData();
	if (tree->Right() != NULL)
	{
		InOrder(tree->Right());
		cout << ")";
	}
}

// outputs arithmetic expression using in-order traversal
int OutputInOrder(Tree *arithmeticTree)
{
	// use recursive in-order tree traversal for output
	cout << "In-fix:" << endl;
	InOrder(arithmeticTree);
	cout << endl;

	return 0;
}

// outputs arithmetic expression using post-order traversal
int OutputPostOrder(Tree *arithmeticTree)
{
	Stack treeStack;
	Tree *temp1 = arithmeticTree, *temp2 = arithmeticTree;

	// step through Arithmetic Tree, creating a Stack of Tree pointers and printing data post-order
	cout << "Post-fix:" << endl;
	while (temp1 != NULL)
	{
		while (temp1->Left() != NULL)
		{
			treeStack.Push(temp1);
			temp1 = temp1->Left();
		}
		while ((temp1->Right() == NULL) || (temp1->Right() == temp2))
		{
			cout << temp1->RootData() << " ";
			temp2 = temp1;
			if (treeStack.IsEmpty() == true)
			{
				cout << endl;
				return 0;
			}
			temp1 = treeStack.Top();
			treeStack.Pop();
		}
		treeStack.Push(temp1);
		temp1 = temp1->Right();
	}

	cout << endl;

	return 0;
}

// creates Arithmetic Tree and outputs expression using in- and post-order traversal
int ArithmeticTree(const char *fileName)
{
	Tree *arithmeticTree;
	
	int error = CreateTree(fileName, arithmeticTree);
	if (error) return error;

	error = OutputInOrder(arithmeticTree);
	if (error) return error;

	error = OutputPostOrder(arithmeticTree);
	if (error) return error;

	return 0;
}

