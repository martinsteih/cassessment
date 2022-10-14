#include "printable.h"

struct printable_vtable_t {
  void (*Print)(const printable_t *const self);
  void (*Destroy)(printable_t *const self);
};

void printable_Print(const printable_t *const self) {
  self->vtable->Print(self);
}
void printable_Destroy(printable_t *const self) { self->vtable->Destroy(self); }