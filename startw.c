#define RAYGUI_IMPLEMENTATION
#include "startw.h"
#include"style_enefete.h"

StartwResult startw_state = NoMode;

StartwResult startw_run(void)
{
  InitWindow(200, 110, "sc");
  GuiLoadStyleEnefete();
  SetTargetFPS(60);
  startw_state = NoMode;
  
  while(!WindowShouldClose())
    {
      if(startw_state != NoMode) break;
      
      BeginDrawing();
      ClearBackground(GetColor(GuiGetStyle(DEFAULT,BACKGROUND_COLOR)));
      _startw_draw();
      EndDrawing();
    }
  CloseWindow();

  return startw_state;
}
void _startw_draw(void)
{
  _startw_draw_start();
}
void _startw_draw_start(void)
{
  GuiLabel((Rectangle){20,10,180,20}, "Choose screenshot mode:");

  if(GuiButton((Rectangle){0,50,200,20}, " [F]ullscreen ") ||
     IsKeyPressed(KEY_F))
    {
      startw_state = FullscreenMode;
    }
  if(GuiButton((Rectangle){0,70,200,20}, "[R]ectangle  ") ||
     IsKeyPressed(KEY_R))
    {
      startw_state = RectangleMode;
    }
  if(GuiButton((Rectangle){0,90,200,20}, "[C]onfig menu") ||
     IsKeyPressed(KEY_C))
    {
      startw_state = ConfigMode;
    }
 
}
