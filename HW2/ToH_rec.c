#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void hanoi(char from, char aux, char to, int n) {
  // printf("Call Hanoi function(%c, %c, %c, %d)\n", from, aux, to, n);
  if (n == 1)
  {
    printf("Move disk 1 from %c to %c\n", from, to);
    return;
  } else {
    hanoi(from, to, aux, n-1);
    printf("Move disk %d from %c to %c\n", n, from, to);
    hanoi(aux, from, to, n-1);
  }
}

int main() {
  printf("ToH using recursive method.\n");
  clock_t begin, end;
  float time_spent;

  int n; // number of disks
  printf("Input the number of disks: ");
  scanf("%d", &n);
  begin = clock();
  hanoi('A', 'B', 'C', n);
  end = clock();
  time_spent = ((float)(end - begin)) / CLOCKS_PER_SEC;
  printf("Number of disks = %d, Time spent: %f\n", n, time_spent);
  return 0;
}

// // print running time for various n without printing the process
// int main() {
//   int n;
//   clock_t begin, end;
//   float time_spent;
//
//   for (int i=0; i<40; i++) {
//     n = i + 1;
//     begin = clock();
//     hanoi('A', 'B', 'C', n);
//     end = clock();
//     time_spent = ((float)(end - begin)) / CLOCKS_PER_SEC;
//     // printf("Number of disks = %d, Time spent: %f\n", n, time_spent);
//     printf("%f\n", time_spent);
//   }
//   return 0;
// }
