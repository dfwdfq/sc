#include "confw.h"
#include"style_enefete.h"

int width = 100, height = 100;
bool width_edit = false, height_edit = false, text_edit = false;
char save_dir[255];

void confw_run(void)
{
  InitWindow(200,150,"sc: config menu");
  GuiLoadStyleEnefete();
  SetTargetFPS(60);
  
  while(!WindowShouldClose())
    {
      BeginDrawing();
      ClearBackground(GetColor(GuiGetStyle(DEFAULT,BACKGROUND_COLOR)));
      _confw_draw();
      EndDrawing();      
    }
  CloseWindow();
}
void _confw_draw(void)
{
  GuiLabel((Rectangle){0,5,150,20}, "#64# Configuration menu");
  GuiLabel((Rectangle){0,30,100,20}, "#119# width:");
  GuiLabel((Rectangle){0,60,100,20}, "#119# height:");
  GuiLabel((Rectangle){0,100,100,20}, "#1# save:");
  
  if(GuiValueBox((Rectangle){65,30,130,20}, NULL, &width, 0, 100, width_edit))
    {
      width_edit = !width_edit;
    }
  if(GuiValueBox((Rectangle){65,60,130,20}, NULL, &height, 0, 100, height_edit))
    {
      height_edit = !height_edit;
    }
  if(GuiTextBox((Rectangle){65,100,130,20}, save_dir, 255, text_edit))
    {
      text_edit = !text_edit;
    }
}

