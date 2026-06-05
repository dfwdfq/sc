#define RAYGUI_IMPLEMENTATION
#include "confw.h"

ConfwResult confw_state = NoMode;

ConfwResult confw_run(void)
{
  InitWindow(200, 110, "sc");
  GuiLoadStyleEnefete();
  SetTargetFPS(60);

  while(!WindowShouldClose())
    {
      if(confw_state != NoMode) break;
      
      BeginDrawing();
      ClearBackground(GetColor(GuiGetStyle(DEFAULT,BACKGROUND_COLOR)));
      _confw_draw();
      EndDrawing();
    }
  CloseWindow();

  return confw_state;
}
void _confw_draw(void)
{
  _confw_draw_start();
}
void _confw_draw_start(void)
{
  GuiLabel((Rectangle){20,10,180,20}, "Choose screenshot mode:");

  if(GuiButton((Rectangle){0,50,200,20}, " [F]ullscreen ") ||
     IsKeyPressed(KEY_F))
    {
      confw_state = FullscreenMode;
    }
  if(GuiButton((Rectangle){0,70,200,20}, "[R]ectangle  ") ||
     IsKeyPressed(KEY_R))
    {
      confw_state = RectangleMode;
    }
  if(GuiButton((Rectangle){0,90,200,20}, "[C]onfig menu") ||
     IsKeyPressed(KEY_C))
    {
      confw_state = ConfigMode;
    }
 
}
