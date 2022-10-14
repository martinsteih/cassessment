#include <stdio.h>
#include <stdlib.h>

#include "object.h"

int main(int argc, char **argv) {
  OBJECT(obj);
  printable_Print((printable_t *const)(&obj));
  printable_Destroy((printable_t *const)(&obj));
  return 0;
}