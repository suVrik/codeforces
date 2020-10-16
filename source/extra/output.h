#pragma once

#include <stdlib.h>

void set_green_text_color();
void set_white_text_color();
void set_gray_text_color();

#define cout (set_green_text_color(), cout)
#define cin  (set_white_text_color(), cin)
#define cerr (set_gray_text_color(),  cerr)

static int clear_text_color_at_exit = atexit(set_white_text_color);
