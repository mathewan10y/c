#include <stdio.h>
int cq[10];
int rear = -1, front = -1;
int item;
void enqueue(int n)
{

    if (front == -1 && rear == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        if (((rear + 1) % n) == front)
        {
            printf("the queue is full");
            return;
        }
        else
            rear = (rear + 1) % n;
    }
    printf("enter element:");
    scanf("%d", &item);
    cq[rear] = item;
    printf("element is inserted\n");
}

void dequeue(int n)
{
    if (front == -1 && rear == -1)
    {
        printf("queue is empty");
        return;
    }
    else
    {
        if (front == rear)
        {
            printf("the deleted item is %d at position %d", cq[front], front);
            front = rear = -1;
        }
        else
        {
            printf("the deleted item is %d at position %d", cq[front], front);
            front = (front + 1) % n;
        }
    }
}

void display(int n)
{
    int i = front, j = rear;
    if (front == -1 && rear == -1)
    {
        printf("the queue is empty\n");
    }
    else
    {

        while (i != -1)
        {
            if (i == j)
            {
                printf("%d at %d \n", cq[i], i);
                i = -1;
            }
            else
            {
                printf("%d at %d \n", cq[i], i);
                i = ((i + 1) % n);
            }
        }
    }
}
void main()
{
    int n;
    printf("enter size of circular queue:");
    scanf("%d", &n);
    int ch;

    while (1)
    {

        printf("\n1.push\n2.pop\n3.display\n4.exit\nenter choice:");
        scanf("%d", &ch);
        if (ch == 1)
        {

            enqueue(n);
        }
        else if (ch == 2)
        {
            dequeue(n);
        }
        else if (ch == 3)
            display(n);
        else if (ch == 4)
        {

            printf("exiting");
            break;
        }
        else
        {
            printf("wrong choice\n");
            continue;
        }
    }
}
