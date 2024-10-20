#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a node in the adjacency list
typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

// Structure to represent the adjacency list
typedef struct Graph
{
    Node *head[MAX_VERTICES];
    int numVertices;
} Graph;

// Function to create a new node
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the graph
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

// Function to add an edge to the graph (undirected)
void addEdge(Graph *graph, int src, int dest)
{
    Node *newNode = createNode(dest);
    newNode->next = graph->head[src];
    graph->head[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->head[dest];
    graph->head[dest] = newNode;
}

// Function to display the graph
void displayGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->head[i];
        printf("Vertex %d: ", i);
        while (temp)
        {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Function for DFS traversal
void DFSUtil(Graph *graph, int vertex, int visited[])
{
    visited[vertex] = 1;
    printf("%d ", vertex);

    Node *temp = graph->head[vertex];
    while (temp)
    {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex])
        {
            DFSUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// Function to perform DFS
void DFS(Graph *graph)
{
    int visited[MAX_VERTICES] = {0};
    for (int i = 0; i < graph->numVertices; i++)
    {
        if (!visited[i])
        {
            DFSUtil(graph, i, visited);
        }
    }
}

// Function to perform BFS
void BFS(Graph *graph, int startVertex)
{
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node *temp = graph->head[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
}

// Main function
int main()
{
    int vertices = 5;
    Graph *graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printf("Graph representation (Adjacency List):\n");
    displayGraph(graph);

    printf("\nDFS traversal:\n");
    DFS(graph);
    printf("\n");

    printf("BFS traversal starting from vertex 0:\n");
    BFS(graph, 0);
    printf("\n");

    // Free memory (not implemented for simplicity)

    return 0;
}
