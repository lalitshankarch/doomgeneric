// doomgeneric for cross-platform development library 'Simple DirectMedia Layer'

#include "constants.h"
#include "doomgeneric.h"
#include "doomkeys.h"
#include "keycodes.h"
#include "m_argv.h"
#include "stubs.h"

#include <ctype.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include <stdbool.h>

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

char *key_press_reg = (char *)(long)REG_KEY_PRESS_LOC;
char *key_code_reg = (char *)(long)REG_KEY_CODE_LOC;

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
  case MYKEY_RCTRL:
    key = KEY_FIRE;
    break;
  case MYKEY_SPACE:
    key = KEY_USE;
    break;
  case MYKEY_LSHIFT:
  case MYKEY_RSHIFT:
    key = KEY_RSHIFT;
    break;
  case MYKEY_LALT:
  case MYKEY_RALT:
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
  case MYKEY_PLUS:
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

static void addKeyToQueue(int pressed, unsigned int keyCode) {
  unsigned char key = convertToDoomKey(keyCode);

  unsigned short keyData = (pressed << 8) | key;

  s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
  s_KeyQueueWriteIndex++;
  s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

void DG_Init() {}

void DG_DrawFrame() {
  _render_frame();

  if (*key_press_reg == 1) {
    addKeyToQueue(1, *key_code_reg);
  } else if (*key_press_reg == 0) {
    addKeyToQueue(0, *key_code_reg);
  }
}

void DG_SleepMs(uint32_t ms) { usleep(ms * 1000); }

uint32_t DG_GetTicksMs() {
  struct timeval tp;
  struct timezone tzp;

  gettimeofday(&tp, &tzp);

  return (tp.tv_sec * 1000) + (tp.tv_usec / 1000); /* return milliseconds */
}

int DG_GetKey(int *pressed, unsigned char *doomKey) {
  if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex) {
    // key queue is empty
    return 0;
  } else {
    unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
    s_KeyQueueReadIndex++;
    s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

    *pressed = keyData >> 8;
    *doomKey = keyData & 0xFF;

    return 1;
  }

  return 0;
}

void DG_SetWindowTitle(const char *title) { (void)title; }

void _start(int argc, char **argv) {
  doomgeneric_Create(argc, argv);

  for (int i = 0;; i++) {
    doomgeneric_Tick();
  }

  exit(0);
}