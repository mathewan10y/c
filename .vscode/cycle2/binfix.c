#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Node structure
typedef struct Node
{
    char value;
    struct Node *left, *right;
} Node;

// Function to create a new node
Node *createNode(char value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to check if a character is an operator
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to get precedence of operators
int precedence(char operator)
{
    if (operator== '+' || operator== '-')
        return 1;
    if (operator== '*' || operator== '/')
        return 2;
    return 0;
}

// Utility function to check if character is operand
int isOperand(char c)
{
    return (c >= '0' && c <= '9') || isalpha(c); // Modify as per your operands (could be digits or variables)
}

// Function to build binary tree from an infix expression
Node *buildTree(char *infix)
{
    Node *stackNodes[100]; // Stack for nodes
    char operators[100];   // Stack for operators
    int topNode = -1, topOp = -1;
    int i = 0;

    while (infix[i] != '\0')
    {
        if (infix[i] == ' ') // Skip spaces
        {
            i++;
            continue;
        }

        if (isOperand(infix[i])) // If operand, create a node and push to node stack
        {
            stackNodes[++topNode] = createNode(infix[i]);
        }
        else if (infix[i] == '(') // If '(', push to operator stack
        {
            operators[++topOp] = infix[i];
        }
        else if (infix[i] == ')') // If ')', pop operators till '(' is found
        {
            while (topOp >= 0 && operators[topOp] != '(')
            {
                Node *rightNode = stackNodes[topNode--];
                Node *leftNode = stackNodes[topNode--];
                Node *operatorNode = createNode(operators[topOp--]);
                operatorNode->left = leftNode;
                operatorNode->right = rightNode;
                stackNodes[++topNode] = operatorNode;
            }
            topOp--; // Pop '(' from the operator stack
        }
        else if (isOperator(infix[i])) // If an operator, apply precedence rules
        {
            while (topOp >= 0 && precedence(operators[topOp]) >= precedence(infix[i]))
            {
                Node *rightNode = stackNodes[topNode--];
                Node *leftNode = stackNodes[topNode--];
                Node *operatorNode = createNode(operators[topOp--]);
                operatorNode->left = leftNode;
                operatorNode->right = rightNode;
                stackNodes[++topNode] = operatorNode;
            }
            operators[++topOp] = infix[i]; // Push current operator to stack
        }
        i++;
    }

    // After the entire expression is processed, pop remaining operators
    while (topOp >= 0)
    {
        Node *rightNode = stackNodes[topNode--];
        Node *leftNode = stackNodes[topNode--];
        Node *operatorNode = createNode(operators[topOp--]);
        operatorNode->left = leftNode;
        operatorNode->right = rightNode;
        stackNodes[++topNode] = operatorNode;
    }

    return stackNodes[topNode]; // The root of the expression tree
}

// Post-order traversal (to get postfix expression)
void postOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    postOrder(node->left);      // Visit left subtree
    postOrder(node->right);     // Visit right subtree
    printf("%c ", node->value); // Visit node
}

// Pre-order traversal (to get prefix expression)
void preOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("%c ", node->value); // Visit node
    preOrder(node->left);       // Visit left subtree
    preOrder(node->right);      // Visit right subtree
}

int main()
{
    char infix[100];
    printf("Enter the infix expression: ");
    fgets(infix, 100, stdin);

    // Build the binary tree from the infix expression
    Node *expressionTree = buildTree(infix);

    // Post-order traversal for postfix
    printf("Postfix expression: ");
    postOrder(expressionTree);
    printf("\n");

    // Pre-order traversal for prefix
    printf("Prefix expression: ");
    preOrder(expressionTree);
    printf("\n");

    return 0;
}