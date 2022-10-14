#include <stdio.h>
#include <stdlib.h>

#include "object.h"

int main(int argc, char **argv) {
  object_t obj;
  obj_Init(&obj);
  obj_Print(&obj);
  obj_SetInt(&obj, 4);
  printf("obj.someint = %d \n", obj_GetInt(&obj));
  obj_Destroy(&obj);
  return 0;
}