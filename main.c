#include <stdio.h>
#include <stdlib.h>

#include "object.h"

typedef enum { IDLE, MOVING, ERROR, MAX_STATES } EState;

typedef struct {
  EState _current;
  EState _new;
  uint8_t _internal_event_generated;
} sm_motor_t;

int main(int argc, char **argv) {
  OBJECT(obj);
  printable_Print((printable_t *const)(&obj));
  printable_Destroy((printable_t *const)(&obj));
  return 0;
}