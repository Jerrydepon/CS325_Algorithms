#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// print the original board with removed square
void print_board(int side, int X_i, int X_j) {

  for (int i = 0; i < side; i++) {
    for (int j = 0; j < side; j++) {
      if (i == X_i && j == X_j)
        printf("X ");
      else
        printf("_ ");
    }
    printf("\n");
  }
  printf("\n");
}

// create a matrix
int **create_array(int length)
{
    int **arr;
    arr = malloc(sizeof(int *) * length);
    for (int i = 0; i < length; i++)
    {
        arr[i] = malloc(sizeof(int) * length);
    }
    for (int j = 0; j < length; j++) {
      for (int k = 0; k < length; k++)
        arr[j][k] = 0;
    }
    return arr;
}

// free the matrix
void free_array(int **arr, int length) {
  for (int i = 0; i < length; i++)
  {
      free(arr[i]);
  }
  free(arr);
}

// use tiles to fill the rest
int tile_it(int side, int X_i, int X_j, int **matrix, int num, int row, int col) {

  if (side == 1)
    return num;

  // 2
  if (X_i < row && X_j < col) {
    // printf("22\n" );
    // printf("number: %d\n", num);
    num = tile_it(side/2, X_i, X_j, matrix, num, row-side/4, col-side/4);
    num = tile_it(side/2, row, col-1, matrix, num, row+side/4, col-side/4);
    num = tile_it(side/2, row, col, matrix, num, row+side/4, col+side/4);
    num = tile_it(side/2, row-1, col, matrix, num, row-side/4, col+side/4);

    matrix[row][col-1] = num;
    matrix[row][col] = num;
    matrix[row-1][col] = num;
  }
  // 3
  else if (X_i >= row && X_j < col) {
    // printf("33\n" );
    // printf("number: %d\n", num);
    num = tile_it(side/2, row-1, col-1, matrix, num, row-side/4, col-side/4);
    num = tile_it(side/2, X_i, X_j, matrix, num, row+side/4, col-side/4);
    num = tile_it(side/2, row, col, matrix, num, row+side/4, col+side/4);
    num = tile_it(side/2, row-1, col, matrix, num, row-side/4, col+side/4);
    matrix[row-1][col-1] = num;
    matrix[row-1][col] = num;
    matrix[row][col] = num;
  }
  // 4
  else if (X_i >= row && X_j >= col) {
    // printf("44\n" );
    // printf("number: %d\n", num);
    num = tile_it(side/2, row-1, col-1, matrix, num, row-side/4, col-side/4);
    num = tile_it(side/2, row, col-1, matrix, num, row+side/4, col-side/4);
    num = tile_it(side/2, X_i, X_j, matrix, num, row+side/4, col+side/4);
    num = tile_it(side/2, row-1, col, matrix, num, row-side/4, col+side/4);
    matrix[row-1][col-1] = num;
    matrix[row][col-1] = num;
    matrix[row-1][col] = num;
  }
  // 1
  else if (X_i < row && X_j >= col) {
    // printf("11\n" );
    // printf("number: %d\n", num);
    num = tile_it(side/2, row-1, col-1, matrix, num, row-side/4, col-side/4);
    num = tile_it(side/2, row, col-1, matrix, num, row+side/4, col-side/4);
    num = tile_it(side/2, row, col, matrix, num, row+side/4, col+side/4);
    num = tile_it(side/2, X_i, X_j, matrix, num, row-side/4, col+side/4);
    matrix[row-1][col-1] = num;
    matrix[row][col-1] = num;
    matrix[row][col] = num;
  }

  return num += 1;
}

void print_matrix(int **matrix, int side, int X_i, int X_j) {
  matrix[X_i][X_j] = -1;
  for (int i = 0; i < side; i++){
    for (int j = 0; j < side; j++) {
      if (matrix[i][j] == -1)
        printf("%-5s", "X");
      else
        printf("%-3d  ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// 1. run one time by input the board size
int main() {
  int side, n, num;
  int random_i, random_j;
  int row = 0, col = 0;

  printf("Enter the power of 2 for length of side: \n");
  scanf("%d", &n);
  side = pow(2, n);

  row += side/2;
  col += side/2;

  int **matrix = create_array(side);

  srand(time(NULL));
  random_i = rand() % side;
  random_j = rand() % side;
  num = 1;

  print_board(side, random_i, random_j);

  tile_it(side, random_i, random_j, matrix, num, row, col);

  print_matrix(matrix, side, random_i, random_j);

  free_array(matrix, side);

  return 0;
}

// // 2. run for various times
// int main() {
//   int side, n, num;
//   int random_i, random_j;
//   int row = 0, col = 0;
//   clock_t begin, end;
//   float time_spent;
//
//   for (int i = 1; i < 100; i++) {
//     row = 0;
//     col = 0;
//
//     side = pow(2, i);
//     row += side/2;
//     col += side/2;
//
//     int **matrix = create_array(side);
//
//     srand(time(NULL));
//     random_i = rand() % side;
//     random_j = rand() % side;
//     num = 1;
//
//     // print_board(side, random_i, random_j);
//
//     begin = clock();
//     tile_it(side, random_i, random_j, matrix, num, row, col);
//     end = clock();
//
//     // print_matrix(matrix, side, random_i, random_j);
//
//     time_spent = ((float)(end - begin)) / CLOCKS_PER_SEC;
//     printf("Time spent for n = %d: %f\n", i, time_spent);
//
//     free_array(matrix, side);
//   }
//   return 0;
// }
