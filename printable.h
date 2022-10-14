#ifndef PRINTABLE_H
#define PRINTABLE_H

struct printable_vtable_t;

typedef struct printable_t {
  struct printable_vtable_t *vtable;
} printable_t;

void printable_Print(const printable_t *const self);
void printable_Destroy(printable_t *const self);

#endif  // PRINTABLE_H