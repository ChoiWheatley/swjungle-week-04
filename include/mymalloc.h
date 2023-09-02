#pragma once
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                           \
  if (!((p) = malloc(s))) {                    \
    fprintf(stderr, "Insufficient memory!\n"); \
    exit(EXIT_FAILURE);                        \
  }