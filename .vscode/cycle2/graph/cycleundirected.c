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

int cycleUtil(Graph *graph, int vertex, int visited[], int parent)
{
    visited[vertex] = 1;

    Node *temp = graph->head[vertex];
    while (temp)
    {
        int adjVertex = temp->vertex;

        if (!visited[adjVertex])
        {
            if (cycleUtil(graph, adjVertex, visited, vertex))
            {
                return 1; // Cycle found
            }
        }
        else if (adjVertex != parent)
        {
            return 1; // Cycle detected (visited node that is not parent)
        }
        temp = temp->next;
    }
    return 0; // No cycle detected
}

int detectCycle(Graph *graph)
{
    int visited[MAX_VERTICES] = {0};

    for (int i = 0; i < graph->numVertices; i++)
    {
        if (!visited[i])
        {
            if (cycleUtil(graph, i, visited, -1))
            {
                return 1; // Cycle detected
            }
        }
    }
    return 0; // No cycle detected
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
    int vertices, edges, src, dest;

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

    printf("\nGraph representation (Adjacency List):\n");
    displayGraph(graph);

    if (detectCycle(graph))
    {
        printf("\nThe graph contains a cycle.\n");
    }
    else
    {
        printf("\nThe graph does not contain a cycle.\n");
    }

    return 0;
}
