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

bool isBipartite(Graph *graph, int startVertex)
{
    int color[MAX_VERTICES];
    for (int i = 0; i < graph->numVertices; i++)
    {
        color[i] = -1; // Initialize all vertices as uncolored (-1)
    }

    color[startVertex] = 0; // Color the start vertex with color 0
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = startVertex;

    while (front < rear)
    {
        int vertex = queue[front++];
        Node *temp = graph->head[vertex];

        while (temp)
        {
            int adjVertex = temp->vertex;

            if (color[adjVertex] == -1)
            {
                // Assign alternate color to the adjacent vertex
                color[adjVertex] = 1 - color[vertex];
                queue[rear++] = adjVertex;
            }
            else if (color[adjVertex] == color[vertex])
            {
                // Found two adjacent vertices with the same color
                return false;
            }

            temp = temp->next;
        }
    }

    return true; // All vertices have been colored correctly
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

    // Check if the graph is bipartite starting from vertex 0
    if (isBipartite(graph, 0))
    {
        printf("The graph is bipartite.\n");
    }
    else
    {
        printf("The graph is not bipartite.\n");
    }

    return 0;
}
