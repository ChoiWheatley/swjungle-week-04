/**
 * 본 파일은 포인터 배열과 배열 포인터, 일반 포인터 사이의 관계를 공부하는
 * 코드들이 담겨있습니다.
 */
#include "../lib/printers.h"
#include <assert.h>
#include <stdio.h>

#define MODULO 10000
#define MOD(x) (long)x % (long)(MODULO)

void array_pointer_1d(void) {
  printf("\n=== start of %s\n\n", __func__);
  int arr[] = {1, 2, 3, 4, 5};
  int *p = arr;
  int(*arrptr)[5] = &arr;
  int *ptrarr[5] = {arr, arr + 1, arr + 2, arr + 3, arr + 4};

  PRINT_L(p);
  PRINT_L(arrptr);
  PRINT_L(ptrarr);
  PRINT_L(arr);
  PRINT_L(&arr);

  printf("\n");

  PRINT_L(*p);
  PRINT_L(*arrptr);
  PRINT_L(*ptrarr);
  PRINT_L(*arr);

  printf("\n");

  PRINT_L(sizeof(p));
  PRINT_L(sizeof(arrptr));
  PRINT_L(sizeof(ptrarr));
  PRINT_L(sizeof(arr));
  PRINT_L(sizeof(&arr));

  printf("\n");

  PRINT_L(sizeof(*p));
  PRINT_L(sizeof(*arrptr));
  PRINT_L(sizeof(*ptrarr));
  PRINT_L(sizeof(*arr));

  printf("\n");

  PRINT_L(&arr[5]);
  PRINT_L(&arr + 1);
  PRINT_L(arrptr + 1);
  PRINT_L(ptrarr + 1);
  printf("\n=== end of %s\n", __func__);
}

void pointer_array_2d(void) {
  printf("\n=== start of %s\n\n", __func__);
  int arr2d[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
  int *ptrarr[3] = {arr2d, arr2d + 1, arr2d + 2, arr2d + 3}; // pointer array
  int(*arrptr)[3] = arr2d; // array pointer which has stride of 3

  PRINT_L(ptrarr[0]);
  PRINT_L(arr2d);
  PRINT_L(*ptrarr);
  PRINT_L(*arrptr);

  printf("\n");

  // arr2d[1][1] = 5를 참조하고 싶다.
  PRINT_D(arr2d[1][1]);
  PRINT_D(*(*(arr2d + 1) + 1));  // go to second element, go to second element
  PRINT_D(*(*(ptrarr + 1) + 1)); // go to second element, go to second element
  PRINT_D(
      *(*(arrptr + 1) + 1)); // go to next stride, deref, go to second element

  printf("\n");

  PRINT_D(sizeof(arr2d));  // 12 * 4 = 48 (whole array 2d)
  PRINT_D(sizeof(ptrarr)); // 8 * 4 = 32 (four pointers)
  PRINT_D(sizeof(arrptr)); // 8 (it's just a pointer! ~~with 3-stride~~)

  printf("\n");
  PRINT_D(sizeof(arr2d));   // 12 * 4 = 48 (whole array 2d)
  PRINT_D(sizeof(*arrptr)); // 4 * 3 = 12 (one row)
  PRINT_D(sizeof(*ptrarr)); // 8 (pointer of each element)

  printf("\n=== end of %s\n", __func__);
}

int main(void) {
  array_pointer_1d();
  pointer_array_2d();

  return 0;
}
void demo() { printf("GeeksQuiz "); }