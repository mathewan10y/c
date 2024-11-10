// a graph is a tree is it is not connected, no cycles, and number of edges = no of vertices-1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool DFS(Graph *graph, int vertex, int visited[], int parent)
{
    visited[vertex] = 1;
    Node *temp = graph->head[vertex];

    while (temp)
    {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex])
        {
            if (DFS(graph, adjVertex, visited, vertex))
            {
                return true;
            }
        }
        else if (adjVertex != parent)
        {
            return true; // Cycle detected
        }
        temp = temp->next;
    }
    return false;
}

bool isTree(Graph *graph)
{
    int visited[MAX_VERTICES] = {0};

    // Check for cycles starting from vertex 0
    if (DFS(graph, 0, visited, -1))
    {
        return false;
    }

    // Check if all vertices are connected
    for (int i = 0; i < graph->numVertices; i++)
    {
        if (!visited[i])
        {
            return false;
        }
    }

    return true;
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

    if (edges != vertices - 1)
    {
        printf("The graph is not a tree (it doesn't have V-1 edges).\n");
    }
    else if (isTree(graph))
    {
        printf("The graph is a tree.\n");
    }
    else
    {
        printf("The graph is not a tree.\n");
    }

    return 0;
}
