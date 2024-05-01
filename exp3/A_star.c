#include <stdio.h>
#include <stdlib.h>
#define ROWS 5
#define COLS 5
typedef struct Node
{
    int row, col;
    int f, g, h;
    struct Node *parent;
} Node;
Node *createNode(int row, int col, int g, int h, Node *parent)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->g = g;
    newNode->h = h;
    newNode->f = g + h;
    newNode->parent = parent;
    return newNode;
}
int isValid(int row, int col)
{
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}
int isDestination(int row, int col, Node *dest)
{
    return (row == dest->row && col == dest->col);
}
int calculateHValue(int row, int col, Node *dest)
{
    return abs(row - dest->row) + abs(col - dest->col);
}
void printPath(Node *node)
{
    if (node == NULL)
        return;
    printPath(node->parent);
    printf("(%d, %d) -> ", node->row, node->col);
}
void aStarSearch(int grid[ROWS][COLS], Node *start, Node *dest)
{
    int visited[ROWS][COLS] = {0};
    int row, col;
    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};
    // Create open and closed lists
    Node *openList[ROWS * COLS];
    int openSize = 0;
    // Add the start node to the open list
    openList[openSize++] = start;
    while (openSize > 0)
    {
        // Find the node with the least f value in the open list
        int currentIdx = 0;
        for (int i = 1; i < openSize; i++)
        {
            if (openList[i]->f < openList[currentIdx]->f)
                currentIdx = i;
        }
        Node *current = openList[currentIdx];
        // Remove the selected node from the open list
        openList[currentIdx] = openList[openSize - 1];
        openSize--;
        // Mark the current node as visited
        visited[current->row][current->col] = 1;
        // Check if destination is reached
        if (isDestination(current->row, current->col, dest))
        {
            printf("Path found! The shortest path is:\n");
            printPath(current);
            return;
        }
        // Explore the neighbors of the current node
        for (int i = 0; i < 4; i++)
        {
            row = current->row + rowNum[i];
            col = current->col + colNum[i];
            // Check if the neighbor is valid and not visited
            if (isValid(row, col) && grid[row][col] && !visited[row][col])
            {
                int gNew = current->g + 1;
                int hNew = calculateHValue(row, col, dest);
                int fNew = gNew + hNew;
                // Check if the neighbor is not in the open list
                int inOpenList = 0;
                for (int j = 0; j < openSize; j++)
                {
                    if (openList[j]->row == row && openList[j]->col == col)
                    {
                        inOpenList = 1;
                        if (fNew < openList[j]->f)
                        {
                            openList[j]->f = fNew;
                            openList[j]->g = gNew;
                            openList[j]->h = hNew;
                            openList[j]->parent = current;
                        }
                        break;
                    }
                }
                // If neighbor is not in the open list, add it
                if (!inOpenList)
                {
                    openList[openSize++] = createNode(row, col, gNew, hNew, current);
                }
            }
        }
    }
    // If the open list is empty and destination is not reached
    printf("Path not found!\n");
}
int main()
{
    int grid[ROWS][COLS] = {
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1}};
    Node *start = createNode(0, 0, 0, 0, NULL);
    Node *dest = createNode(4, 4, 0, 0, NULL);
    aStarSearch(grid, start, dest);
    return 0;
}
