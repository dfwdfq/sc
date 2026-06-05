#ifndef X11SCREENSHOT_H
#define X11SCREENSHOT_H

#include <stdint.h>

typedef struct
{
  uint8_t *data;   
  int width;
  int height;
} X11Image;

extern X11Image take_x11_screenshot(void);

#endif /* X11SCREENSHOT_H */
