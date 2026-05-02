#pragma once

#ifndef MEM_SIZE
#define MEM_SIZE (1024 * 1024 * 8)
#endif

#ifndef QUEUE_SIZE
#define QUEUE_SIZE (32)
#endif

#ifndef QUEUE_START
#define QUEUE_START (MEM_SIZE - QUEUE_SIZE - 1)
#endif

#ifndef QUEUE_READ_IDX
#define QUEUE_READ_IDX (QUEUE_START - 1)
#endif

#ifndef QUEUE_WRITE_IDX
#define QUEUE_WRITE_IDX (QUEUE_READ_IDX - 1)
#endif

#ifndef VRAM_SIZE
#define VRAM_SIZE (640 * 400 * 4)
#endif

#ifndef VRAM_START
#define VRAM_START (QUEUE_WRITE_IDX - VRAM_SIZE)
#endif

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH (640)
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT (400)
#endif