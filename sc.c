#define RAYGUI_IMPLEMENTATION
#include "sc.h"
#include"style_enefete.h"

State sc_state = StartMenu;

void sc_run(void)
{
  InitWindow(200, 110, "sc");
  GuiLoadStyleEnefete();
  SetTargetFPS(60);
  
  while(!WindowShouldClose())
    {      
      BeginDrawing();
      ClearBackground(GetColor(GuiGetStyle(DEFAULT,BACKGROUND_COLOR)));
      switch(sc_state)
	{
	case StartMenu:
	  _startw_draw();
	  break;
	case ConfMenu:
	  _confw_draw();
	  break;
	}
      EndDrawing();
    }
  CloseWindow();

}
