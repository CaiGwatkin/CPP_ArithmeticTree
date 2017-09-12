#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// defines Tree class used to store arithmetic expression
class Tree {
private:
    char data;
    Tree *leftPointer, *rightPointer;

public:
    Tree(const char newData, Tree *left, Tree *right);              // Tree constructor
    ~Tree() { }                                                     // Tree destructor
    char RootData() { return data; }                                // returns the data stored in the Tree's root
    Tree* Left() { return leftPointer; }                            // returns a pointer to the left Tree
    Tree* Right() { return rightPointer;  }                         // returns a pointer to the right Tree
};

// defines Nodes of a linked list for the Stack
struct Node
{
    Tree *treePointer;
    Node *next;
};

// defines Stack class which stores Arithmetic Tree pointers in a linked list
class Stack
{
private:
    Node *listPointer;

public:
    Stack();                                                        // Stack constructor
    ~Stack();                                                       // Stack destructor
    void Push(Tree *t);                                             // adds a Tree pointer to the top of the Stack
    void Pop();                                                     // removes the top Tree pointer from the Stack
    bool IsEmpty();                                                 // checks if the Stack is empty
    Tree* Top();                                                    // returns the Tree pointer from the top of the Stack
};


int ErrArguments();                                                 // returns error code if there are not enough arguments passed to the program
int ErrFile(const char *fileName);                                  // returns error code if the file cannot be opened
void AddDigit(const char digit, Stack &treeCreation);               // adds a digit to the Stack (create new Tree)
void AddOperator(const char oper, Stack &treeCreation);             // adds an operator to the Stack (create new Tree)
int CreateTree(const char *fileName, Tree *&arithmeticTree);        // creates Arithmetic Tree from RPN text file
void InOrder(Tree *tree);                                           // recursive in-order tree traversal for output
int OutputInOrder(Tree *arithmeticTree);                            // outputs arithmetic expression using in-order traversal
int OutputPostOrder(Tree *arithmeticTree);                          // outputs arithmetic expression using post-order traversal
int ArithmeticTree(const char *fileName);                           // creates Arithmetic Tree and outputs expression using in- and post-order traversal
