#include <stdio.h>
int rear = -1, front = -1;
int item;

struct pque
{
    int data;
    int prio;
} pq[20], temp[20];

void addpq(int n)
{
    int i;
    if (rear == n - 1)
    {
        printf("queue is full");
    }

    else
    {
        rear++;
        printf("enter item");
        scanf("%d", &pq[rear].data);
        printf("enter priority");
        scanf("%d", &pq[rear].prio);

        for (i = rear; i > front; i--)
        {
            if (pq[i].prio > pq[i - 1].prio)
            {
                temp[0] = pq[i];
                pq[i] = pq[i - 1];
                pq[i - 1] = temp[0];
            }
        }
        printf("element inserted");
    }
}

void delpq()
{
    if (front == rear)
        printf("priority queue is empty");

    else
    {
        printf("the deleted element is %d ,having priority %d", pq[front].data, pq[front].prio);
        front++;
    }
}

void displaypq()

{
    if (front == rear)
        printf("queue is empty");
    int i;
    for (i = front; i < rear; i++)
        printf("%d %d\t  ", pq[i].data, pq[i].prio);
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
            addpq(n);
        }
        else if (ch == 2)
            delpq();
        else if (ch == 3)
            displaypq();
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
