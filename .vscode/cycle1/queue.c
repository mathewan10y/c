#include <stdio.h>
int queue[10];
int item, front = -1, rear = -1;
void push(int n)
{
    if (rear == n - 1)
        printf("queue is full");
    else
    {
        printf("enter element");
        scanf("%d", &item);
        rear++;
        queue[rear] = item;
    }
}

void pop()
{
    if (front == rear)
    {
        printf("the queue is empty");
        front = -1;
        rear = -1;
    }
    else
    {
        front++;
        printf("The deleted element is %d at position %d", queue[front], front);
    }
}

void display()
{
    if (front == rear)
        printf("queue is empty");
    int i;
    for (i = front + 1; i <= rear; i++)
    {
        printf("%d at %d\n", queue[i], i);
    }
}

void main()
{
    int n;
    printf("enter size of queue");
    scanf("%d", &n);
    int ch;
    while (1)
    {
        printf("\n1.push\n2.pop\n3.display\n4.exit\nenter choice:");
        scanf("%d", &ch);
        if (ch == 1)
        {
            push(n);
        }
        else if (ch == 2)
            pop();
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
