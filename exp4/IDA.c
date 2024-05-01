#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 5 // Number of vertices

// Function to calculate straight line distance between two nodes
int calculateDistance(int graph[V][V], int path[], int len)
{
    int distance = 0;
    for (int i = 0; i < len - 1; i++)
    {
        distance += graph[path[i]][path[i + 1]];
    }
    return distance;
}

// Function to perform Depth Limited Search (DLS)
int DLS(int graph[V][V], int src, int target, int depth, int path[])
{
    if (src == target)
        return 1;
    if (depth <= 0)
        return 0;
    for (int i = 0; i < V; i++)
    {
        if (graph[src][i] && DLS(graph, i, target, depth - 1, path))
        {
            path[depth - 1] = i;
            return 1;
        }
    }
    return 0;
}

// Function to perform Iterative Deepening Search (IDS)
void iterativeDeepeningSearch(int graph[V][V], int src, int target)
{
    int maxDepth = INT_MAX;
    for (int depth = 1; depth <= maxDepth; depth++)
    {
        int path[depth + 1]; // Increased path length by 1
        path[0] = src;
        if (DLS(graph, src, target, depth, path + 1))
        { // Adjusted path pointer
            printf("Path found with total distance: %d units\nThe path is from: ", calculateDistance(graph, path, depth + 1));
            for (int i = 0; i <= depth; i++)
            {
                printf("%d", path[i]);
                if (i < depth)
                {
                    printf(" -> ");
                }
            }
            printf("\n");
            return;
        }
    }
    printf("Path does not exist.\n");
}

int main()
{
    int graph[V][V] = {
        {0, 2, 0, 0, 3},
        {2, 0, 4, 0, 0},
        {0, 4, 0, 6, 0},
        {0, 0, 6, 0, 8},
        {3, 0, 0, 8, 0}};
    int src = 0;    // Source node
    int target = 4; // Target node
    iterativeDeepeningSearch(graph, src, target);
    return 0;
}
