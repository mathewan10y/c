#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100
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
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

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

void infixToPostfix(char infix[MAX], char postfix[MAX])
{
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++)
    {
        if (isalnum(infix[i]))
        {
            // Handle multi-digit numbers
            while (isalnum(infix[i]))
            {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; // space to separate variables
            i--;                // Adjust index back
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

void infixToPrefix(char infix[MAX], char prefix[MAX])
{
    reverse(infix);
    top = -1; // Reset stack for prefix conversion
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++)
    {
        if (isalnum(infix[i]))
        {
            while (isalnum(infix[i]))
            {
                prefix[j++] = infix[i++];
            }
            prefix[j++] = ' '; // space to separate variables
            i--;               // Adjust index back
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
            pop(); // remove ')' from stack
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

double evaluatePostfix(char postfix[MAX])
{
    double stack[MAX];
    int top = -1;

    char *token = strtok(postfix, " ");
    while (token != NULL)
    {
        if (isdigit(token[0]))
        {
            // Convert token to double and push to stack
            stack[++top] = atof(token);
        }
        else if (isOperator(token[0]) && top >= 1)
        {
            // Assume valid operator with enough operands
            double b = stack[top--]; // Pop second operand
            double a = stack[top--]; // Pop first operand
            switch (token[0])
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
        token = strtok(NULL, " ");
    }

    return (top == 0) ? stack[top] : 0; // Ensure one final result
}

// Main program
int main()
{
    char infix[MAX], postfix[MAX], prefix[MAX];
    while (1)
    {

        printf("Menu:\n");
        printf("1. Convert to Postfix\n");
        printf("2. Convert to Prefix\n");
        printf("3. Exit\n");
        printf("Choose an option: ");

        int choice;
        scanf("%d", &choice);
        if (choice == 3)
            break;
        printf("Enter the infix expression: ");
        scanf(" %[^\n]", infix); // Read entire line including spaces

        if (!isEvaluable(infix))
        {
            printf("Invalid expression! Only valid characters are allowed.\n");
            continue;
        }

        // Check if the infix expression contains any alphabetic characters
        int containsAlpha = 0;
        for (int i = 0; infix[i] != '\0'; i++)
        {
            if (isalpha(infix[i]))
            {
                containsAlpha = 1;
                break;
            }
        }
        if (choice == 1)
        {
            infixToPostfix(infix, postfix);
            printf("Postfix Expression: %s\n", postfix);
            if (!containsAlpha)
            {
                printf("Evaluation Result: %.2f\n", evaluatePostfix(postfix));
            }
        }
        else if (choice == 2)
        {
            infixToPrefix(infix, prefix);
            printf("Prefix Expression: %s\n", prefix);
        }

        else
        {
            printf("Invalid choice! Please choose 1, 2, or 3.\n");
        }
    }
    return 0;
}
