#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
int eval = 0;
char stack[MAX];
int top = -1;

// Stack functions
void push(char item)
{
    if (top < MAX - 1)
    {
        stack[++top] = item;
    }
}

char pop()
{
    if (top != -1)
    {
        return stack[top--];
    }
    return '\0';
}

int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return 0;
}

int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to check if the expression is evaluable
int isEvaluable(char infix[MAX])
{
    for (int i = 0; infix[i] != '\0'; i++)
    {
        if (!isalnum(infix[i]) && !isOperator(infix[i]) && infix[i] != '(' && infix[i] != ')')
        {
            return 0; // Invalid character found
        }
    }
    return 1; // Expression is evaluable
}

// Function to convert infix to postfix
void infixToPostfix(char infix[MAX], char postfix[MAX])
{
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++)
    {

        if (isalnum(infix[i]))
        {
            postfix[j++] = infix[i];
            if (isalpha(infix[i]))
                eval = 1;
            postfix[j++] = ' '; // space to separate variables
        }
        else if (infix[i] == '(')
        {
            push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (top != -1 && (stack[top]) != '(')
            {
                postfix[j++] = pop();
                postfix[j++] = ' '; // space to separate operators
            }
            pop(); // remove '(' from stack
        }
        else if (isOperator(infix[i]))
        {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i]))
            {
                postfix[j++] = pop();
                postfix[j++] = ' '; // space to separate operators
            }
            push(infix[i]);
        }
    }

    while (top != -1)
    {
        postfix[j++] = pop();
        postfix[j++] = ' '; // space to separate operators
    }
    postfix[j] = '\0'; // null-terminate the string
}

// Function to reverse a string
void reverse(char str[MAX])
{
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++)
    {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Function to convert infix to prefix
void infixToPrefix(char infix[MAX], char prefix[MAX])
{
    reverse(infix);
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++)
    {

        if (isalnum(infix[i]))
        {
            prefix[j++] = infix[i];
            prefix[j++] = ' '; // space to separate variables
        }
        else if (infix[i] == ')')
        {
            push(infix[i]);
        }
        else if (infix[i] == '(')
        {
            while (top != -1 && (stack[top]) != ')')
            {
                prefix[j++] = pop();
                prefix[j++] = ' '; // space to separate operators
            }
            pop(); // remove '(' from stack
        }
        else if (isOperator(infix[i]))
        {
            while (top != -1 && precedence(stack[top]) > precedence(infix[i]))
            {
                prefix[j++] = pop();
                prefix[j++] = ' '; // space to separate operators
            }
            push(infix[i]);
        }
    }

    while (top != -1)
    {
        prefix[j++] = pop();
        prefix[j++] = ' '; // space to separate operators
    }
    prefix[j] = '\0'; // null-terminate the string

    reverse(prefix);
}

// Function to evaluate a postfix expression
double evaluatePostfix(char postfix[MAX])
{
    double stack[MAX];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        if (isdigit(postfix[i]))
        {
            // Convert character to integer and push to stack
            stack[++top] = postfix[i] - '0'; // Push single-digit number
        }
        else if (postfix[i] == ' ')
        {
            continue; // Skip spaces
        }
        else
        {
            // Assume valid operator with enough operands
            double b = stack[top--]; // Pop second operand
            double a = stack[top--]; // Pop first operand
            switch (postfix[i])
            {
            case '+':
                stack[++top] = a + b;
                break;
            case '-':
                stack[++top] = a - b;
                break;
            case '*':
                stack[++top] = a * b;
                break;
            case '/':
                stack[++top] = a / b;
                break;
            }
        }
    }

    return (top == 0) ? stack[top] : 0; // Ensure one final result
}

// Main program
int main()
{
    char infix[MAX], postfix[MAX], prefix[MAX];
    int choice;
    while (1)
    {
        printf("Enter the infix expression: ");
        scanf(" %[^\n]", infix); // Read entire line including spaces

        if (!isEvaluable(infix))
        {
            printf("Invalid expression! Only valid characters are allowed.\n");
            continue;
        }

        printf("Menu:\n");
        printf("1. Convert to Postfix\n");
        printf("2. Convert to Prefix\n");
        printf("3.exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            infixToPostfix(infix, postfix);
            printf("Postfix Expression: %s\n", postfix);

            // Evaluate the postfix expression if it contains numbers
            if (eval == 0)
            {
                printf("Evaluation Result: %.2f\n", evaluatePostfix(postfix));
            }
        }
        else if (choice == 2)
        {
            infixToPrefix(infix, prefix);
            printf("Prefix Expression: %s\n", prefix);
        }
        else if (choice == 3)
            break;
        else
        {
            printf("Invalid choice! Please choose 1 or 2.\n");
        }
    }
    return 0;
}
