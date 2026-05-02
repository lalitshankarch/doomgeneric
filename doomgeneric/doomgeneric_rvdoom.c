// doomgeneric for cross-platform development library 'Simple DirectMedia Layer'

#include "constants.h"
#include "doomgeneric.h"
#include "doomkeys.h"
#include "keycodes.h"
#include "stubs.h"

#include <ctype.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include <stdbool.h>

static unsigned char convertToDoomKey(unsigned int key) {
  switch (key) {
  case MYKEY_RETURN:
    key = KEY_ENTER;
    break;
  case MYKEY_ESCAPE:
    key = KEY_ESCAPE;
    break;
  case MYKEY_LEFT:
    key = KEY_LEFTARROW;
    break;
  case MYKEY_RIGHT:
    key = KEY_RIGHTARROW;
    break;
  case MYKEY_UP:
    key = KEY_UPARROW;
    break;
  case MYKEY_DOWN:
    key = KEY_DOWNARROW;
    break;
  case MYKEY_LCTRL:
    key = KEY_FIRE;
    break;
  case MYKEY_SPACE:
    key = KEY_USE;
    break;
  case MYKEY_LSHIFT:
    key = KEY_RSHIFT;
    break;
  case MYKEY_LALT:
    key = KEY_LALT;
    break;
  case MYKEY_F2:
    key = KEY_F2;
    break;
  case MYKEY_F3:
    key = KEY_F3;
    break;
  case MYKEY_F4:
    key = KEY_F4;
    break;
  case MYKEY_F5:
    key = KEY_F5;
    break;
  case MYKEY_F6:
    key = KEY_F6;
    break;
  case MYKEY_F7:
    key = KEY_F7;
    break;
  case MYKEY_F8:
    key = KEY_F8;
    break;
  case MYKEY_F9:
    key = KEY_F9;
    break;
  case MYKEY_F10:
    key = KEY_F10;
    break;
  case MYKEY_F11:
    key = KEY_F11;
    break;
  case MYKEY_EQUALS:
    key = KEY_EQUALS;
    break;
  case MYKEY_MINUS:
    key = KEY_MINUS;
    break;
  default:
    key = tolower(key);
    break;
  }

  return key;
}

static unsigned char *sp_KeyQueueWriteIndex =
    (unsigned char *)(long)QUEUE_WRITE_IDX;
static unsigned char *sp_KeyQueueReadIndex =
    (unsigned char *)(long)QUEUE_READ_IDX;
;
static unsigned short *sp_Queue = (unsigned short *)(long)QUEUE_START;

void DG_Init() {}

void DG_DrawFrame() { _render_frame(); }

void DG_SleepMs(uint32_t ms) { usleep(ms * 1000); }

uint32_t DG_GetTicksMs() {
  struct timeval tp;
  struct timezone tzp;

  gettimeofday(&tp, &tzp);

  return (tp.tv_sec * 1000) + (tp.tv_usec / 1000); /* return milliseconds */
}

int DG_GetKey(int *pressed, unsigned char *doomKey) {
  if (*sp_KeyQueueReadIndex == *sp_KeyQueueWriteIndex) {
    // key queue is empty
    return 0;
  } else {
    unsigned short keyData = sp_Queue[*sp_KeyQueueReadIndex];
    (*sp_KeyQueueReadIndex)++;
    *sp_KeyQueueReadIndex %= 16;

    *pressed = keyData >> 8;
    *doomKey = convertToDoomKey(keyData & 0xFF) & 0xFF;

    // printf("read idx: %d, pressed: %d, doomKey: %d\n", *sp_KeyQueueReadIndex,
    //        *pressed, *doomKey);

    return 1;
  }

  return 0;
}

void DG_SetWindowTitle(const char *title) { (void)title; }

void _start(void) {
  doomgeneric_Create(0, NULL);

  for (int i = 0;; i++) {
    doomgeneric_Tick();
  }

  exit(0);
}