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

void topologicalSortUtil(Graph *graph, int vertex, int visited[], int stack[])
{
    visited[vertex] = 1;

    Node *temp = graph->head[vertex];
    while (temp)
    {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex])
        {
            topologicalSortUtil(graph, adjVertex, visited, stack);
        }
        temp = temp->next;
    }

    // Push the current vertex to the stack
    stack[vertex] = 1;
}

void topologicalSort(Graph *graph)
{
    int visited[MAX_VERTICES] = {0};
    int stack[MAX_VERTICES] = {0};

    // Call the helper function to perform DFS and store the topological order
    for (int i = 0; i < graph->numVertices; i++)
    {
        if (!visited[i])
        {
            topologicalSortUtil(graph, i, visited, stack);
        }
    }

    // Print the topological sort
    printf("\nTopological Sort of the Graph:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        if (stack[i] == 1)
        {
            printf("%d ", i);
        }
    }
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

    topologicalSort(graph);

    return 0;
}
