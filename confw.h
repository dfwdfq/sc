/*
  configuration window
*/  
#ifndef CONFW_H
#define CONFW_H
#include<raylib.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdio.h>
#include"raygui.h"

extern int width, height;
extern bool width_edit, height_edit, text_edit;
extern char save_dir[255];

extern void confw_run(void);
extern void _confw_draw(void);

#endif /* CONFW_H */

