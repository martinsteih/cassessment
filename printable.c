#include "printable.h"

struct printable_vtable_t {
  uint8_t (*Print)(const printable_t *const self);
  void (*Destroy)(printable_t *const self);
};

uint8_t printable_Print(const printable_t *const self) {
  if (!self || !self->vtable) {
    return -1;
  }
  return self->vtable->Print(self);
}
void printable_Destroy(printable_t *const self) {
  if (self && self->vtable) {
    self->vtable->Destroy(self);
  }
}