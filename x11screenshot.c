#include "x11screenshot.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>

X11Image take_x11_screenshot(void)
{
  X11Image result = {NULL, 0, 0};
  Display *dpy = XOpenDisplay(NULL);
  if (!dpy)
    return result;

  int screen = DefaultScreen(dpy);
  Window root = RootWindow(dpy, screen);
  int width = DisplayWidth(dpy, screen);
  int height = DisplayHeight(dpy, screen);
  
  XImage *image = XGetImage(dpy, root, 0, 0, width, height, AllPlanes, ZPixmap);
    if (!image)
      {
        XCloseDisplay(dpy);
        return result;
      }
    
    uint8_t *data = malloc(width * height * 4);
    if (!data)
      {
        XDestroyImage(image);
        XCloseDisplay(dpy);
        return result;
      }

    for (int y = 0; y < height; y++)
      {
        for (int x = 0; x < width; x++)
	  {
            unsigned long pixel = XGetPixel(image, x, y);
            uint8_t *dst = data + (y * width + x) * 4;
            dst[0] = (pixel & image->red_mask) >> 16;
            dst[1] = (pixel & image->green_mask) >> 8;
            dst[2] = (pixel & image->blue_mask);
            dst[3] = 255;
	  }
      }
    
    XDestroyImage(image);
    XCloseDisplay(dpy);
    
    result.data = data;
    result.width = width;
    result.height = height;
    return result;
}
