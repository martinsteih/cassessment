#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>

#include "printable.h"

/**
 * @brief
 *
 */
typedef struct object_t {
  printable_t printable;
  uint8_t _some_int;
} object_t;

/**
 * @brief Macro to instantiate an object of object_t without forgetting to call
 * obj_Init
 *
 */
#define OBJECT(_name_) \
  object_t _name_;     \
  obj_Init(&_name_)

/**
 * @brief
 *
 * @param self
 */
void obj_Init(object_t *const self);

/**
 * @brief
 *
 * @param self
 */
uint8_t obj_Print(object_t *const self);

/**
 * @brief
 *
 * @param self
 */
void obj_Destroy(object_t *const self);

/**
 * @brief
 *
 * @param self
 * @param newint
 */
void obj_SetInt(object_t *const self, uint8_t newint);

/**
 * @brief
 *
 * @param self
 * @return uint8_t
 */
uint8_t obj_GetInt(const object_t *const self);

#endif  // OBJECT_H