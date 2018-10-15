#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int divide_into_three(int i, int* coin, int coin_num, int* weight_num) {
  int sum1 = 0, sum2 = 0, sum3 = 0;
  int start, odd_coin_position;

  // divide into three parts & sum each part
  for (int j = i; j < i+coin_num/3; j++)
    sum1 += coin[j];
  for (int j = i+coin_num/3; j < i+2*coin_num/3; j++)
    sum2 += coin[j];
  for (int j = i+2*coin_num/3; j < i+coin_num; j++)
    sum3 += coin[j];

  // take the part with odd coin & recursive if necessary
  coin_num = coin_num/3;
  if (coin_num != 1) {
    if (sum1 == sum2) {
      *weight_num += 1;
      start = i+2*coin_num;
      odd_coin_position = divide_into_three(start, coin, coin_num, weight_num);
    }
    else if (sum1 == sum3) {
      *weight_num += 2;
      start = i+coin_num;
      odd_coin_position = divide_into_three(start, coin, coin_num, weight_num);
    }
    else {
      *weight_num += 2;
      start = i;
      odd_coin_position = divide_into_three(start, coin, coin_num, weight_num);
    }
  }
  // find the odd coin
  else {
    if (sum1 == sum2) {
      odd_coin_position = i+2;
      *weight_num += 1;
    }
    else if (sum1 == sum3) {
      odd_coin_position = i+1;
      *weight_num += 2;
    }
    else {
      odd_coin_position = i;
      *weight_num += 2;
    }
  }

  return odd_coin_position;
}

// 1. print only one result according to user input
int main() {

  int n, coin_num, index_of_odd, random_odd_pos, random_odd_weight;
  int weight_num = 0;
  srand(time(NULL));

  // build a array for total coins
  printf("Enter the power of 3 for number of coins: \n");
  scanf("%d", &n);
  coin_num = pow(3, n);
  int coin[coin_num];
  for (int i = 0; i < coin_num; i++) {
    coin[i] = 2;
  }

  // use random umber to decide where the odd coin is
  random_odd_pos = rand() % coin_num;
  random_odd_weight = rand() % 2;
  if (random_odd_weight == 0)
    random_odd_weight = 1;
  else
    random_odd_weight = 3;
  // printf("%d\n", random_odd_pos);
  coin[random_odd_pos] = random_odd_weight;

  // print the array of total coin with odd coin
  for (int i = 0; i < coin_num; i++) {
    printf("%d  ", coin[i]);
  }
  printf("\n");

  // recursive call & the result
  index_of_odd = divide_into_three(0, coin, coin_num, &weight_num);
  printf("The odd coin is at: %d\n", index_of_odd);
  printf("Number of weighings is: %d\n", weight_num);
  if (coin[index_of_odd] > 2)
    printf("Odd coin is heavier!\n");
  else
    printf("Odd coin is lighter!\n");

  return 0;
}

// // 2. print various results of same number of total coin
// int main() {
//   int n, index_of_odd, random_odd_pos, random_odd_weight;
//   int weight_num = 0;
//   float time_spent;
//   int coin_num;
//   int num_call;
//
//   for (int i = 1; i < 10; i++) {
//     weight_num = 0;
//
//     coin_num = pow(3, 3);
//     int coin[coin_num];
//     for (int i = 0; i < coin_num; i++) {
//       coin[i] = 2;
//     }
//
//     // use random umber to decide where the odd coin is
//     random_odd_pos = rand() % coin_num;
//     random_odd_weight = rand() % 2;
//     if (random_odd_weight == 0)
//       random_odd_weight = 1;
//     else
//       random_odd_weight = 3;
//     coin[random_odd_pos] = random_odd_weight;
//
//     for (int i = 0; i < coin_num; i++) {
//       printf("%d  ", coin[i]);
//     }
//     printf("\n");
//
//     index_of_odd = divide_into_three(0, coin, coin_num, &weight_num);
//
//     printf("The odd coin is at: %d\n", index_of_odd);
//     printf("Number of weighings is: %d\n", weight_num);
//     if (coin[index_of_odd] > 2)
//       printf("Odd coin is heavier!\n\n");
//     else
//       printf("Odd coin is lighter!\n\n");
//   }
//   return 0;
// }

// // 3. print the running time & number of weighings
// int main() {
//   int n, index_of_odd, random_odd_pos, random_odd_weight;
//   int weight_num = 0;
//   srand(time(NULL));
//   clock_t begin, end;
//   float time_spent;
//   int coin_num;
//   int num_call;
//   float total_time;
//   int total_weighing;
//   float mean_time, mean_weighing;
//
//   for (int j = 1; j < 14; j++) {
//     total_time = 0;
//     total_weighing = 0;
//     mean_time = 0.0;
//     mean_weighing = 0.0;
//
//     for (int i = 1; i < 11; i++) {
//       weight_num = 0;
//
//       coin_num = pow(3, j);
//       int coin[coin_num];
//       for (int i = 0; i < coin_num; i++) {
//         coin[i] = 2;
//       }
//
//       // use random umber to decide where the odd coin is
//       random_odd_pos = rand() % coin_num;
//       random_odd_weight = rand() % 2;
//       if (random_odd_weight == 0)
//         random_odd_weight = 1;
//       else
//         random_odd_weight = 3;
//       // printf("%d\n", random_odd_pos);
//       coin[random_odd_pos] = random_odd_weight;
//
//       begin = clock();
//       index_of_odd = divide_into_three(0, coin, coin_num, &weight_num);
//       end = clock();
//
//       time_spent = ((float)(end - begin)) / CLOCKS_PER_SEC;
//       printf("Time spent for %d coins: %f, Number of weighings is: %d\n", coin_num, time_spent, weight_num);
//       total_time += time_spent;
//       total_weighing += weight_num;
//     }
//     mean_time = total_time / 10;
//     mean_weighing = ((float)total_weighing) / 10.0;
//     printf("mean time: %f, mean weighing: %f\n\n", mean_time, mean_weighing);
//   }
//   return 0;
// }
