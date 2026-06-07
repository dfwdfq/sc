#include "sc.h"



bool width_edit = false, height_edit = false, text_edit = false, step_edit = false;
char save_dir[255] ="~/Pictures";

void _confw_draw(void)
{
  GuiLabel((Rectangle){0,5,150,20}, "#64# Configuration menu");
  GuiLabel((Rectangle){0,30,100,20}, "#119#  width:");
  GuiLabel((Rectangle){0,50,100,20}, "#119# height:");
  GuiLabel((Rectangle){0,70,100,20}, "#119#   step:");
  GuiLabel((Rectangle){0,100,100,20}, "#1#   save:");
  
  if(GuiValueBox((Rectangle){65,30,130,20}, NULL, &width, 0, 1920, width_edit))
    {
      width_edit = !width_edit;
    }
  if(GuiValueBox((Rectangle){65,50,130,20}, NULL, &height, 0, 1080, height_edit))
    {
      height_edit = !height_edit;
    }
  if(GuiValueBox((Rectangle){65,70,130,20}, NULL, &step, 0, 50, step_edit))
    {
      step_edit = !step_edit;
    }
  if(GuiTextBox((Rectangle){65,100,130,20}, save_dir, 255, text_edit))
    {
      text_edit = !text_edit;
    }

  if(GuiButton((Rectangle){65,125,130,20}, "[B]ack") ||
     IsKeyPressed(KEY_B))
    {
      SetWindowSize(200, 110);
      sc_state = StartMenu;
    }
}

