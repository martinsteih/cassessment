#include <stdio.h>
#include <stdlib.h>

#include "object.h"

typedef enum { IDLE, MOVING, ERROR, MAX_STATES } EState;
enum { IMPOSSIBLE = 0xFF };

typedef struct {
  EState _current;
  EState _new;
  uint8_t _eventGenerated;
  void *_eventData;
} sm_motor_t;

typedef struct {
  void (*sm_state)(sm_motor_t *const self, void *const pData);
  void (*sm_entry)(sm_motor_t *const self, void *const pData);
  uint8_t (*sm_guard)(sm_motor_t *const self, void *const pData);
  void (*sm_exit)(sm_motor_t *const self);
} sm_state_t;

typedef struct {
  const size_t _MAX_STATES;
  const sm_state_t _TRANSITION_MAP[MAX_STATES];
} sm_motor_const_t;

void sm_engine(sm_motor_t *const self,
               const sm_motor_const_t *const selfConst) {
  if (!self || !selfConst) {
    return;  // ToDo: replace with proper management or assert
  }

  while (self->_eventGenerated) {
    if (self->_new >= selfConst->_MAX_STATES) {
      return;  // ToDo: like above
    }
    void *pDataTmp = self->_eventData;
    self->_eventData = NULL;
    self->_eventGenerated = 0;
    if ((selfConst->_TRANSITION_MAP[self->_current].sm_guard &&
         selfConst->_TRANSITION_MAP[self->_current].sm_guard(self, pDataTmp)) ||
        !(selfConst->_TRANSITION_MAP[self->_current].sm_guard)) {
      if (self->_new != self->_current) {
        if (selfConst->_TRANSITION_MAP[self->_current].sm_exit) {
          selfConst->_TRANSITION_MAP[self->_current].sm_exit(self);
        }
        if (selfConst->_TRANSITION_MAP[self->_new].sm_entry) {
          selfConst->_TRANSITION_MAP[self->_new].sm_entry(self, pDataTmp);
        }
      }
      self->_current = self->_new;
      if (selfConst->_TRANSITION_MAP[self->_current].sm_state) {
        selfConst->_TRANSITION_MAP[self->_current].sm_state(self, pDataTmp);
      }
    }
    if (pDataTmp) {
      free(pDataTmp);
      pDataTmp = NULL;
    }
  }
}

void sm_internal_event(sm_motor_t *const self, EState newState,
                       void *const pData) {
  if (self) {
    self->_eventData = pData;
    self->_eventGenerated = 1;
    self->_new = newState;
  }
}

void sm_external_event(sm_motor_t *const self,
                       const sm_motor_const_t *const selfConst, EState newState,
                       void *const pData) {
  if (newState == IMPOSSIBLE) {
    if (pData) free(pData);
  } else {
    sm_internal_event(self, newState, pData);
    sm_engine(self, selfConst);
  }
}

//========= End State Machine ==================

typedef struct {
  const sm_motor_const_t _sm_constants;
  sm_motor_t _sm_current_state;
} motor_t;

void motor_event_move(motor_t *const self, void *const pData) {
  static const EState transitions[] = {MOVING, MOVING, IMPOSSIBLE};
  sm_external_event((sm_motor_t *const)&(self->_sm_current_state),
                    (sm_motor_const_t *const)&(self->_sm_constants),
                    transitions[self->_sm_current_state._current], pData);
}

void motor_event_stop(motor_t *const self) {}

void motor_event_quit_error(motor_t *const self) {}

/**
 * @brief
 *
 * @todo move motor_data to ist own file and encapsule data and interface in
 * order to be able to check the boundaries without leaving the user the
 * opportunity of interfering with the interface.
 *
 */
typedef struct {
  uint64_t setpoint_speed;
  uint64_t setpoint_pos;
  uint32_t command_word;
} motor_data_t;

void motor_init(motor_t *const self) {}

void motor_move(sm_motor_t *const self, void *const pData) {
  printf("moving\n");
}

int main(int argc, char **argv) {
  OBJECT(obj);
  printable_Print((printable_t *const)(&obj));
  printable_Destroy((printable_t *const)(&obj));

  motor_t motor = {._sm_constants = {MAX_STATES,
                                     {{NULL, NULL, NULL, NULL},
                                      {motor_move, NULL, NULL, NULL},
                                      {NULL, NULL, NULL, NULL}}}};
  motor_init(&motor);
  motor_data_t *const setpoints = calloc(sizeof(motor_data_t), 1);
  motor_event_move((motor_t *const)&(motor), (void *const)(setpoints));
  return 0;
}