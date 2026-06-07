#include "sc.h"


void _startw_draw(void)
{
  GuiLabel((Rectangle){20,10,180,20}, "Choose screenshot mode:");

  if(GuiButton((Rectangle){0,50,200,20}, " [F]ullscreen ") ||
     IsKeyPressed(KEY_F))
    {
      sc_state = FullscreenMode;      
    }
  if(GuiButton((Rectangle){0,70,200,20}, "[R]ectangle  ") ||
     IsKeyPressed(KEY_R))
    {
      sc_state = RectangleMode;
      before_rect_wpos = GetWindowPosition();
      int m = GetCurrentMonitor();
      SetWindowPosition(0, 0);
      SetWindowSize(GetMonitorWidth(m), GetMonitorWidth(m));
    }
  if(GuiButton((Rectangle){0,90,200,20}, "[C]onfig menu") ||
     IsKeyPressed(KEY_C))
    {      
      SetWindowSize(200, 150);
      sc_state = ConfMenu;
    }  
}

