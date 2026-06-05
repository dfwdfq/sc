#define RAYGUI_IMPLEMENTATION
#include "sc.h"
#include"style_enefete.h"

State sc_state = StartMenu;
int width = 250;
int height=200;

void sc_run(void)
{
  SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_TOPMOST);
  InitWindow(200, 110, "sc");
  GuiLoadStyleEnefete();
  SetTargetFPS(60);

  while(!WindowShouldClose())
    {
      BeginDrawing();
      
      if(sc_state == FullscreenMode ||
	 sc_state == RectangleMode)
	ClearBackground(BLANK);
      else
	ClearBackground(GetColor(GuiGetStyle(DEFAULT,BACKGROUND_COLOR)));
      
      switch(sc_state)
	{
	case StartMenu:
	  _startw_draw();
	  break;
	case ConfMenu:
	  _confw_draw();
	  break;
	case FullscreenMode:
	  take_fullscreen_pic();
	  break;
	case RectangleMode:
	  take_rectangle_pic();
	  break;
	}
      
      EndDrawing();

    }
  CloseWindow();
}
void take_rectangle_pic(void)
{
  if(IsKeyReleased(KEY_LEFT) ||
     IsKeyPressed(KEY_A))
    {
      //width-=1;
    }
  

  if(IsKeyReleased(KEY_ENTER) ||
     IsKeyPressed(KEY_SPACE))
    {
      Vector2 pos = GetWindowPosition();

      X11Image ximg = take_x11_screenshot((int)pos.x,
					  (int)pos.y,
					  width,
					  height);
      save_img(&ximg);
      
      sc_state = StartMenu;
      SetWindowSize(200, 110);
      SetWindowPosition(pos.x, pos.y);
    }
}
void take_fullscreen_pic(void)
{
  SetWindowSize(1, 1);
  SetWindowPosition(-1, -1);
  Vector2 pos = GetWindowPosition();
  WaitTime(1.0);
  
  X11Image ximg = take_x11_screenshot(-1,-1,-1,-1);
  save_img(&ximg);

  sc_state = StartMenu;
  SetWindowSize(200, 110);
  SetWindowPosition(pos.x, pos.y);
}
void save_img(X11Image* ximg)
{
  if (!ximg->data)
    {
      fprintf(stderr,"Failed to capture screenshot\n");
      sc_state = StartMenu;
      SetWindowSize(200, 110);
      return;
    }
  
  Image screenshot =
    {
      .data = ximg->data,
      .width = ximg->width,
      .height = ximg->height,
      .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
      .mipmaps = 1
    };

  
  char full[1024];
  char name[255];
  get_file_name(name);
  if(save_dir[0] == '~')    
    {
      char* dir = expand_homedir(save_dir);
      sprintf(full,"%s%s.png",dir,name);
      free(dir);
    }
  else
    {
      sprintf(full,"%s%s.png",save_dir,name);
    }
  
  ExportImage(screenshot, full);
  UnloadImage(screenshot);   
}
