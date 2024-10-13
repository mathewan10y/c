#include <stdio.h>
int top = -1, n;
int stack[20];
int item;
void push(int item, int n)
{
    if (top == n - 1)
    {
        printf("stack full");
    }
    else
    {
        top++;
        stack[top] = item;
    }
}

void pop()
{
    if (top == -1)
        printf("the stack is empty");
    else
    {

        printf("The deleted element is %d", stack[top]);
        top--;
    }
}

void display()
{
    int i;
    for (i = 0; i <= top; i++)
    {
        printf("%d\t", stack[i]);
    }
}
void main()
{
    int n;
    printf("enter size of stack");
    scanf("%d", &n);
    int ch;

    while (1)
    {

        printf("\n1.push\n2.pop\n3.display\n4.exit\nenter choice:");
        scanf("%d", &ch);
        if (ch == 1)
        {
            printf("enter element");
            scanf("%d", &item);

            push(item, n);
        }
        else if (ch == 2)
        {
            pop();
        }
        else if (ch == 3)
            display();
        else if (ch == 4)
        {
            printf("exiting");
            break;
        }
        else
        {
            printf("wrong choice");
            continue;
        }
    }
}
