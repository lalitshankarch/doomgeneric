#pragma once

const int MEM_SIZE = 1024 * 1024 * 8;
const int QUEUE_SIZE = 32;
const int QUEUE_START = MEM_SIZE - QUEUE_SIZE - 1;
const int QUEUE_READ_IDX = QUEUE_START - 1;
const int QUEUE_WRITE_IDX = QUEUE_READ_IDX - 1;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 400;