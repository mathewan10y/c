// directed graph
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
}

int countPathsUtil(Graph *graph, int src, int dest, int visited[])
{
    if (src == dest)
    {
        return 1;
    }

    visited[src] = 1;
    int pathCount = 0;

    Node *temp = graph->head[src];
    while (temp)
    {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex])
        {
            pathCount += countPathsUtil(graph, adjVertex, dest, visited);
        }
        temp = temp->next;
    }

    visited[src] = 0; // Backtrack
    return pathCount;
}

int countPaths(Graph *graph, int src, int dest)
{
    int visited[MAX_VERTICES] = {0};
    return countPathsUtil(graph, src, dest, visited);
}

int main()
{
    int vertices, edges, src, dest, startVertex, endVertex;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    Graph *graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the directed edges (src dest):\n");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Enter the start and end vertices for path count: ");
    scanf("%d %d", &startVertex, &endVertex);

    int pathCount = countPaths(graph, startVertex, endVertex);
    printf("Number of paths from %d to %d: %d\n", startVertex, endVertex, pathCount);

    return 0;
}
