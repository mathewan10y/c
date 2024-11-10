#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph
{
    Node *head[MAX_VERTICES];
    int numVertices;
} Graph;

Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++)
    {
        graph->head[i] = NULL;
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest)
{
    Node *newNode = createNode(dest);
    newNode->next = graph->head[src];
    graph->head[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->head[dest];
    graph->head[dest] = newNode;
}

void BFS(Graph *graph, int start, int end, int parent[])
{
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear)
    {
        int current = queue[front++];
        Node *temp = graph->head[current];

        while (temp)
        {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = 1;
                parent[adjVertex] = current;
                queue[rear++] = adjVertex;

                if (adjVertex == end)
                {
                    return; // Found the end vertex
                }
            }
            temp = temp->next;
        }
    }
}

void printShortestPath(int parent[], int start, int end)
{
    if (end == -1)
    {
        printf("No path found.\n");
        return;
    }

    if (start == end)
    {
        printf("%d ", start);
        return;
    }

    printShortestPath(parent, start, parent[end]);
    printf("-> %d ", end);
}

void displayGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->head[i];
        printf("Vertex %d:", i);
        while (temp)
        {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main()
{
    int vertices, edges, src, dest, start, end;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    Graph *graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (src dest):\n");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("\nEnter the start and end vertices for the shortest path: ");
    scanf("%d %d", &start, &end);

    int parent[MAX_VERTICES];
    for (int i = 0; i < vertices; i++)
    {
        parent[i] = -1;
    }

    BFS(graph, start, end, parent);

    printf("\nShortest path from %d to %d: ", start, end);
    printShortestPath(parent, start, end);
    printf("\n");

    return 0;
}
