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

void printPath(int path[], int pathLength)
{
    for (int i = 0; i < pathLength; i++)
    {
        printf("%d ", path[i]);
    }
    printf("\n");
}

void findAllPathsUtil(Graph *graph, int src, int dest, int visited[], int path[], int pathIndex)
{
    visited[src] = 1;
    path[pathIndex] = src;
    pathIndex++;

    if (src == dest)
    {
        printPath(path, pathIndex); // Print the path when destination is reached
    }
    else
    {
        Node *temp = graph->head[src];
        while (temp)
        {
            if (!visited[temp->vertex])
            {
                findAllPathsUtil(graph, temp->vertex, dest, visited, path, pathIndex);
            }
            temp = temp->next;
        }
    }

    pathIndex--;
    visited[src] = 0; // Backtrack
}

void findAllPaths(Graph *graph, int startVertex, int endVertex)
{
    int visited[MAX_VERTICES] = {0};
    int path[MAX_VERTICES];
    int pathIndex = 0;

    printf("All paths from %d to %d:\n", startVertex, endVertex);
    findAllPathsUtil(graph, startVertex, endVertex, visited, path, pathIndex);
}

int main()
{
    int vertices, edges, src, dest, startVertex, endVertex;

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

    printf("Enter the start and end vertices to find paths: ");
    scanf("%d %d", &startVertex, &endVertex);

    findAllPaths(graph, startVertex, endVertex);

    return 0;
}
