#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// structure of stack
struct Stack {
  unsigned capacity;
  int top;
  int *array;
};

// create a stack
struct Stack* createStack(unsigned capacity)
{
  struct Stack* stack = malloc(sizeof(struct Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = malloc(stack->capacity * sizeof(int));
  return stack;
}

// determine if stack is empty
int isEmpty(struct Stack* stack)
{
  return (stack->top == -1);
}

// determine if stack is full
int isFull(struct Stack* stack)
{
  return (stack->top == stack->capacity - 1);
}

// pop from top
int pop(struct Stack* stack)
{
  if (isEmpty(stack))
    return 0;
  else {
    return stack->array[stack->top--];
  }
}

// push to top
void push(struct Stack *stack, int item)
{
  if (isFull(stack))
    return;
  else {
    stack->top++;
    stack->array[stack->top] = item;
  }
}

// print the movement of disks
void printMovement(char from, char to, int n)
{
  printf("Move disk %d from %c to %c\n", n, from, to);
}

// implement legal movement between two poles
void moveBetween(struct Stack *src, struct Stack *dest, char s, char d) {
  int pole1TopDisk = pop(src);
  int pole2TopDisk = pop(dest);

  if (pole1TopDisk == 0) {
    push(src, pole2TopDisk);
    printMovement(d, s, pole2TopDisk);
  }

  else if (pole2TopDisk == 0) {
    push(dest, pole1TopDisk);
    printMovement(s, d, pole1TopDisk);
  }

  else if (pole1TopDisk > pole2TopDisk) {
    push(src, pole1TopDisk);
    push(src, pole2TopDisk);
    printMovement(d, s, pole2TopDisk);
  }

  else if (pole1TopDisk < pole2TopDisk) {
    push(dest, pole2TopDisk);
    push(dest, pole1TopDisk);
    printMovement(s, d, pole1TopDisk);
  }
}

// main function to implement iterative ToH
void iterationToH(struct Stack* src, struct Stack *aux, struct Stack *dest, int n) {
  int i;
  unsigned long long total_moves;
  char s = 'A', d = 'C', a = 'B'; // A, B, C poles

  // if n is even, interchange destination pole and auxiliary pole
  if (n % 2 == 0) {
    char temp = d;
    d = a;
    a  = temp;
  }

  total_moves = pow(2, n) - 1;

  // push from the largest disk to source
  for (i = n; i >= 1; i--)
    push(src, i);

  for (i = 1; i <= total_moves; i++) {
    if (i % 3 == 1)
      moveBetween(src, dest, s, d);
    else if (i % 3 == 2)
      moveBetween(src, aux, s, a);
    else if (i % 3 == 0)
      moveBetween(aux, dest, a, d);
  }
}

int main() {
  printf("ToH using iterative method.\n");

  int n; // number of disks
  clock_t begin, end;
  float time_spent;

  printf("Input the number of disks: ");
  scanf("%d", &n);
  begin = clock();

  struct Stack *source, *auxiliary, *destination;

  // create three stacks, size is equals to n
  source = createStack(n);
  auxiliary = createStack(n);
  destination = createStack(n);

  iterationToH(source, auxiliary, destination, n);
  end = clock();
  time_spent = ((float)(end - begin)) / CLOCKS_PER_SEC;
  printf("Time spent: %f\n", time_spent);

  return 0;
}

// // print running time for various n without printing the process
// int main() {
//   int n; // number of disks
//   clock_t begin, end;
//   float time_spent;
//   struct Stack *source, *auxiliary, *destination;
//
//   for (int i = 0; i < 35; i++) {
//     n = i + 1;
//     begin = clock();
//     // create three stacks, size is equals to n
//     source = createStack(n);
//     auxiliary = createStack(n);
//     destination = createStack(n);
//
//     iterationToH(source, auxiliary, destination, n);
//     end = clock();
//     time_spent = ((float)(end - begin)) / CLOCKS_PER_SEC;
//     // printf("Number of disks = %d, Time spent: %f\n", n, time_spent);
//     printf("%f\n", time_spent);
//   }
//   return 0;
// }
