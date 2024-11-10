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

// Helper function to remove a single directed edge from src to dest
void removeDirectedEdge(Graph *graph, int src, int dest)
{
    Node *temp = graph->head[src];
    Node *prev = NULL;

    while (temp != NULL && temp->vertex != dest)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL)
    {
        if (prev == NULL)
        {
            graph->head[src] = temp->next;
        }
        else
        {
            prev->next = temp->next;
        }
        free(temp);
    }
}

// Function to remove an undirected edge
void removeEdge(Graph *graph, int src, int dest)
{
    removeDirectedEdge(graph, src, dest);
    removeDirectedEdge(graph, dest, src);
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

    printf("Enter an edge to remove (src dest): ");
    scanf("%d %d", &src, &dest);
    removeEdge(graph, src, dest);

    printf("\nGraph after removing the edge:\n");
    displayGraph(graph);

    return 0;
}
