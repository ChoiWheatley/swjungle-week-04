#include "../include/len.h"
#include <stdio.h>

int main(void) {
  int arr[5] = {1, 2, 3, 4, 5};
  printf("%ld\n", LEN(arr, int));
  return 0;
}