/*
  start window
*/  
#ifndef STARTW_H
#define STARTW_H
#include<raylib.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdio.h>
#include"raygui.h"
#include"style_enefete.h"

typedef enum StartwResult
{
  FullscreenMode,
  RectangleMode,
  ConfigMode,
  NoMode
} StartwResult;
extern StartwResult startw_state;

extern StartwResult startw_run(void);
extern void _startw_draw(void);

extern void _startw_draw_start(void);

#endif /* STARTW_H */
