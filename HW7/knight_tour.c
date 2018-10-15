#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Move pattern on basis of the change of x coordinates and y coordinates respectively
// check next move clockwise from {2, -1}
static int x_move[8] = {2, 1, -1, -2, -2, -1, 1, 2};
static int y_move[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int board_size;
int open_num = 0, close_num = 0, notFound_num = 0;

// function restricts the knight to remain within the NxN chessboard
int limits(int x, int y) {
    return ((x >= 0 && y >= 0) && (x < board_size && y < board_size));
}

// Checks whether a square is valid and empty or not
int isempty(int *int_array, int x, int y) {
    return (limits(x, y)) && (int_array[y * board_size + x] < 0);
}

// Returns the number of empty squares adjacent to (x, y)
int getDegree(int *int_array, int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (isempty(int_array, (x + x_move[i]), (y + y_move[i])))
            count++;
    }

    return count;
}

// Picks next point using Warnsdorff's heuristic.
// Returns false if it is not possible to pick next point.
int nextMove(int *int_array, int *x, int *y) {
    int min_deg_idx = -1, degree, min_deg = 8, x_next, y_next;
    // Try all board_size adjacent of (*x, *y) starting from a random adjacent.
    // Find the adjacent with minimum degree.
    int start = 0;
    for (int count = 0; count < 8; count++) {
        int i = (start + count) % 8;
        x_next = *x + x_move[i];
        y_next = *y + y_move[i];

        degree = getDegree(int_array, x_next, y_next);
        // print checking path
        if ((isempty(int_array, x_next, y_next)) && degree <= min_deg) {
            min_deg_idx = i;
            min_deg = degree;
        }
    }
    // IF we could not find a next cell
    if (min_deg_idx == -1)
        return 0;

    // Store coordinates of next point
    x_next = *x + x_move[min_deg_idx];
    y_next = *y + y_move[min_deg_idx];

    // Mark next move
    int_array[y_next * board_size + x_next] = int_array[(*y) * board_size + (*x)] + 1;

    // Update next point
    *x = x_next;
    *y = y_next;

    return 1;
}

// displays the chessboard with all the legal knight's moves
void print_board(int *int_array) {
    for (int j = 0; j < board_size; j++) {
        for (int i = 0; i < board_size; i++)
            printf("%d\t", int_array[j * board_size + i]);
        printf("\n");
    }
    printf("\n");
}

// checks its neighbouring sqaures, if the knight ends on a square that is one
// knight's move from the beginning square, then tour is closed
int neighbour(int x, int y, int init_x, int init_y) {
    for (int i = 0; i < board_size; i++) {
        if (((x + x_move[i]) == init_x) && ((y + y_move[i]) == init_y))
            return 1;
    }

    return 0;
}

// Generates the legal moves using warnsdorff's heuristics. Returns false if not possible
int getTour(int *int_array, int decide_row, int decide_col) {
    // Filling up the chessboard matrix with -1's int_array[n * n];
    for (int i = 0; i < board_size * board_size; i++)
        int_array[i] = -1;

    // Random initial position || base on the input to decide initial position
    int init_x = decide_row == -1 ? rand() % board_size : decide_col;
    int init_y = decide_col == -1 ? rand() % board_size : decide_row;

    // Current points are the same as initial points
    int x = init_x, y = init_y;
    int_array[y * board_size + x] = 1; // Mark first move.

    // Keep picking next points using Warnsdorff's heuristic
    for (int i = 0; i < board_size * board_size - 1; i++) {
        if (nextMove(int_array, &x, &y) == 0) {
            notFound_num++;
            printf("\n<<can not find the tour>>\n\n");
            print_board(int_array);
            return 0;
        }
    }

    // Check if tour is closed (Can end at starting point)
    if (!neighbour(x, y, init_x, init_y)) {
        open_num++;
        printf("\n<<open tour>>\n\n");
    }
    else {
        close_num++;
        printf("\n<<closed tour>>\n\n");
    }
    print_board(int_array);
    return 1;
}

// Nomrmal process running for one time
int main() {
    printf("\nkey in the n for the n*n board\n");
    scanf("%d", &board_size);

    int *int_array = malloc(sizeof(int) * board_size * board_size);

    // To make sure that different random initial positions are picked.
    srand(time(NULL));

    getTour(int_array, -1, -1);

    return 0;
}

// // Check the total number of each initial
// int main() {
//
//     printf("\nkey in the n for the n*n board\n");
//     scanf("%d", &board_size);
//
//     int *int_array = malloc(sizeof(int) * board_size * board_size);
//
//     // To make sure that different random initial positions are picked.
//     srand(time(NULL));
//
//     // loop through all the solutions
//     for (int row = 0; row < board_size; row++) {
//         for (int col = 0; col < board_size; col++)
//             getTour(int_array, row, col);
//     }
//     printf("open tour: %d\nclose tour: %d\nnot found: %d\n\n", open_num, close_num, notFound_num);
//
//     return 0;
// }
