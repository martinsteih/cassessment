#include <stdio.h>

#include "object.h"

struct object_vtable {
  void (*Print)(object_t *const self);
  void (*Destroy)(object_t *const self);
};

void obj_Init(object_t *const self) {
  static struct object_vtable vtable = {.Print = obj_Print,
                                        .Destroy = obj_Destroy};
  self->printable.vtable = (struct printable_vtable_t *)(&vtable);
  self->_some_int = 0;
}
void obj_Print(object_t *const self) { printf("object_t::print\n"); }
void obj_Destroy(object_t *const self) { printf("obj::Destroy\n"); }

void obj_SetInt(object_t *const self, const uint8_t newint) {
  self->_some_int = newint;
}
uint8_t obj_GetInt(const object_t *const self) { return self->_some_int; }