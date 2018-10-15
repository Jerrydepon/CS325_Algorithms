#include <stdio.h>
#include <stdlib.h>

unsigned int n, num;
char** checkerboard;
int* column;
int* right; // right oblique
int* left; // left oblique

void print_board() {
  printf("\n");
  for(int i = 0; i < n; i++)
  {
      for(int j = 0; j < n; j++)
      {
          printf("%c", checkerboard[i][j]);
      }
      printf("\n");
  }
}

void put_queens(int x) {
  int j, k;
  if (x < n) {
      for (int i = 0; i < n; i++) {
          j = i - x + n - 1;
          k = i + x;

          if (column[i] && right[j] && left[k]) {
              column[i] = right[j] = left[k] = 0;
              checkerboard[x][i] = 'Q';

              put_queens(x + 1);

              column[i] = right[j] = left[k] = 1;
              checkerboard[x][i] = 'x';
          }
      }
  }
  // when reaching the end of row
  else {
      print_board();
      num++;
  }
}

void create_array() {
  column = malloc(sizeof(int) * n);
  right = malloc(sizeof(int) * (2 * n - 1));
  left = malloc(sizeof(int) * (2 * n - 1));
  checkerboard = malloc(sizeof(char*) * n);
}

void init_array() {
  int i, j;
  num = 0;
  for (i = 0; i < n; i++) {
      column[i] = 1;

      checkerboard[i] = malloc(sizeof(char) * n);
      for (j = 0; j < n; j++) {
          checkerboard[i][j] = 'x';
      }
  }

  for (i = 0; i < 2 * n - 1; i++) {
      right[i] = left[i] = 1;
  }
}

void free_all() {
  for (int i = 0; i < n; i++) {
      free(checkerboard[i]);
  }
  free(checkerboard);
  free(column);
  free(right);
  free(left);
}

int main() {
  int i, j;

  printf("Please enter the number of n: ");
  scanf("%d", &n);

  create_array();

  init_array();

  put_queens(0);

  printf("\nWhen n = %d, there are %d ways of putting queens.\n\n", n, num);

  free_all();

  return 0;
}
