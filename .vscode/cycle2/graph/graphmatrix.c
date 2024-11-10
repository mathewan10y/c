#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Graph
{
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Function to create a graph with a specified number of vertices
Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // Initialize the adjacency matrix with 0 (no edges)
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Function to add an edge between two vertices (for an undirected graph)
void addEdge(Graph *graph, int src, int dest)
{
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1; // Remove this line for a directed graph
}

// Function to display the adjacency matrix
void displayGraph(Graph *graph)
{
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Depth-First Search (DFS) utility function
void DFSUtil(Graph *graph, int vertex, int visited[])
{
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < graph->numVertices; i++)
    {
        if (graph->adjMatrix[vertex][i] == 1 && !visited[i])
        {
            DFSUtil(graph, i, visited);
        }
    }
}

// Function to perform DFS on the entire graph
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
    printf("\n");
}

// Breadth-First Search (BFS)
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

        for (int i = 0; i < graph->numVertices; i++)
        {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i])
            {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
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

    printf("\nGraph representation (Adjacency Matrix):\n");
    displayGraph(graph);

    printf("\nDFS traversal:\n");
    DFS(graph);

    printf("BFS traversal starting from vertex 0:\n");
    BFS(graph, 0);

    // Free the graph memory
    free(graph);

    return 0;
}
