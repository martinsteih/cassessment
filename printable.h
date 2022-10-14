#ifndef PRINTABLE_H
#define PRINTABLE_H
#include <stdint.h>

struct printable_vtable_t;

typedef struct printable_t {
  const struct printable_vtable_t *vtable;
} printable_t;

uint8_t printable_Print(const printable_t *const self);
void printable_Destroy(printable_t *const self);

#endif  // PRINTABLE_H