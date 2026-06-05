#ifndef SC_H
#define SC_H
#include<raylib.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdio.h>
#include<time.h>
#include"raygui.h"
#include"x11screenshot.h"

typedef enum State
{
  StartMenu,
  ConfMenu,
  FullscreenMode,
  RectangleMode,
} State;

extern State sc_state;

//confw.c
extern int width, height;
extern bool width_edit, height_edit, text_edit;
extern char save_dir[255];


extern void sc_run(void);
extern void take_fullscreen_pic(void);
extern void take_rectangle_pic(void);
extern void save_img(X11Image* ximg);

//startw.c
extern void _startw_draw(void);

//confw.c
extern void _confw_draw(void);

//util.c
extern void get_file_name(char* output);
extern char* expand_homedir(char* path);

#endif /* SC_H */
