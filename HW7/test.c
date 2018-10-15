// 933-295-313
// Webster Cheng
// CS 325.002
// HW #7
// Feb 28, 2018
// Need std=c99
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Move pattern on basis of the change of
// x coordinates and y coordinates respectively
static int ktMoveCol[8] = {2, 1, -1, -2, -2, -1, 1, 2};
static int ktMoveRow[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int sizeNum, openTour, cloTour, notFd;

void print(int *a);

// function restricts the knight to remain within
// the NxN chessboard
int isLimits(int x, int y)
{
    return ((x >= 0 && y >= 0) && (x < sizeNum && y < sizeNum));
}

/* Checks whether a square is valid and empty or not */
int isempty(int *a, int x, int y)
{
    return (isLimits(x, y)) && (a[y * sizeNum + x] < 0);
}

/* Returns the number of empty squares adjacent
   to (x, y) */
int getDegree(int *a, int x, int y)
{
    int count = 0;
    for (int i = 0; i < 8; ++i)
        if (isempty(a, (x + ktMoveCol[i]), (y + ktMoveRow[i])))
            count++;

    return count;
}

// Picks next point using Warnsdorff's heuristic.
// Returns false if it is not possible to pick
// next point.
int moveKnight(int *ktMap, int *x, int *y)
{
    int minDegIdx = -1, c, minDeg = 8, nextCol, nextRow;
    // Try all sizeNum adjacent of (*x, *y) starting
    // from a random adjacent. Find the adjacent
    // with minimum degree.
    int start = 0;
    for (int count = 0; count < 8; ++count)
    {
        int i = (start + count) % 8;
        nextCol = *x + ktMoveCol[i];
        nextRow = *y + ktMoveRow[i];

        c = getDegree(ktMap, nextCol, nextRow);
        /*print checking path*/
        if ((isempty(ktMap, nextCol, nextRow)) && c <= minDeg)
        {
            minDegIdx = i;
            minDeg = c;
        }
    }

    // IF we could not find a next cell
    if (minDegIdx == -1)
        return 0;

    // Store coordinates of next point
    nextCol = *x + ktMoveCol[minDegIdx];
    nextRow = *y + ktMoveRow[minDegIdx];

    // Mark next move
    ktMap[nextRow * sizeNum + nextCol] = ktMap[(*y) * sizeNum + (*x)] + 1;

    // Update next point
    *x = nextCol;
    *y = nextRow;

    return 1;
}

/* displays the chessboard with all the
  legal knight's moves */
void printBoard(int *a)
{
    for (int row = 0; row < sizeNum; row++)
    {
        for (int col = 0; col < sizeNum; col++)
            printf("%d\t", a[row * sizeNum + col]);
        printf("\n");
    }
}

/* checks its neighbouring sqaures */
/* If the knight ends on a square that is one
   knight's move from the beginning square,
   then tour is closed */
int neighbour(int x, int y, int xx, int yy)
{
    for (int i = 0; i < sizeNum; ++i)
        if (((x + ktMoveCol[i]) == xx) && ((y + ktMoveRow[i]) == yy))
            return 1;

    return 0;
}

/* Generates the legal moves using warnsdorff's
  heuristics. Returns false if not possible */
int findKnightTour(int *knightMap, int inputCol, int inputRow)
{
    // Filling up the chessboard matrix with -1's
    for (int i = 0; i < sizeNum * sizeNum; ++i)
        knightMap[i] = -1;

    // Randome initial position
    int initCol = inputCol == -1 ? rand() % sizeNum : inputCol;
    int initRow = inputRow == -1 ? rand() % sizeNum : inputRow;

    // Current points are same as initial points
    int x = initCol, y = initRow;
    knightMap[y * sizeNum + x] = 1; // Mark first move.

    // Keep picking next points using
    // Warnsdorff's heuristic
    for (int i = 0; i < sizeNum * sizeNum - 1; ++i)
        if (moveKnight(knightMap, &x, &y) == 0)
        {
            notFd++;
            printf("Can not find the solution!!\n");
            printBoard(knightMap);
            return 0;
        }

    // Check if tour is closed (Can end
    // at starting point)
    if (!neighbour(x, y, initCol, initRow))
    {
        openTour++;
        printf("Tour is open!!\n");
    }
    else
    {
        cloTour++;
        printf("Tour is closed!!\n");
    }

    printBoard(knightMap);
    return 1;
}

// // Driver code
int main()
{
    openTour = cloTour = notFd = 0;
    // To make sure that different random
    // initial positions are picked.
    srand(time(NULL));
    // printf("Input the n*n board\n");
    // scanf("%d", &sizeNum);
    sizeNum = 5;
    int *knightMap = malloc(sizeof(int) * sizeNum * sizeNum);
    for (int row = 0; row < sizeNum; row++)
    {
        for (int col = 0; col < sizeNum; col++)
            findKnightTour(knightMap, col, row);
    }
    printf("Open Tour: %d close tour: %d not found: %d\n",openTour,cloTour,notFd);
    free(knightMap);
    return 0;
}

// Driver code
// int main()
// {
//     // To make sure that different random
//     // initial positions are picked.
//     srand(time(NULL));
//     printf("Input the n*n board\n");
//     scanf("%d", &sizeNum);
//     int *knightMap = malloc(sizeof(int) * sizeNum * sizeNum);
//     findKnightTour(knightMap, -1, -1);
//     free(knightMap);
//     system("pause");
//     return 0;
// }
