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

    printf("\nDFS traversal:\n");
    DFS(graph);
    printf("\n");

    printf("BFS traversal starting from vertex 0:\n");
    BFS(graph, 0);
    printf("\n");

    return 0;
}
