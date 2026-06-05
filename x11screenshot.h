#ifndef X11SCREENSHOT_H
#define X11SCREENSHOT_H

#include <stdint.h>

typedef struct
{
  uint8_t *data;   
  int width;
  int height;
} X11Image;

//if all arguments are -1, then fullscreen
extern X11Image take_x11_screenshot(int start_x,
				    int start_y,
				    int win_width,
				    int win_height);

#endif /* X11SCREENSHOT_H */
