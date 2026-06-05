#ifndef SC_H
#define SC_H
#include<raylib.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdio.h>
#include"raygui.h"

typedef enum State
{
  StartMenu,
  ConfMenu,
} State;

extern State sc_state;

//confw.c
extern int width, height;
extern bool width_edit, height_edit, text_edit;
extern char save_dir[255];


extern void sc_run(void);

//startw.c
extern void _startw_draw(void);

//confw.c
extern void _confw_draw(void);

#endif /* SC_H */
