#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>

/**
 * @brief
 *
 */
typedef struct object_t {
  uint8_t _some_int;
} object_t;

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
void obj_Print(object_t *const self);

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