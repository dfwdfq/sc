#define RAYGUI_IMPLEMENTATION
#include "sc.h"
#include"style_enefete.h"

State sc_state = StartMenu;
int width = 250;
int height= 200;
int step  = 1;
int rx = 100;
int ry = 100;
Color rect_color = MAGENTA;
Vector2 before_rect_wpos;
char last_save[1060];
bool image_failed = false;
char error_message[256];

void sc_run(void)
{
  SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_UNDECORATED);
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
	  SetExitKey(KEY_NULL);
	  take_rectangle_pic();
	  break;
	case MessageBox:
	  draw_message_box();
	  break;
	}

      EndDrawing();

    }
  CloseWindow();
}
void take_rectangle_pic(void)
{
  draw_rect();
  
  if(IsKeyReleased(KEY_A) ||
     IsKeyReleased(KEY_LEFT))
    {
      rx-=step;
    }
  if(IsKeyReleased(KEY_D) ||
     IsKeyReleased(KEY_RIGHT))
    {
      rx+=step;
    }
  if(IsKeyReleased(KEY_S) ||
     IsKeyReleased(KEY_DOWN))
    {
      ry+=step;
    }
  if(IsKeyReleased(KEY_W) ||
     IsKeyReleased(KEY_UP))
    {
      ry-=step;
    }


  if(IsKeyReleased(KEY_C))
    {
      if(width > step)
	width-=step;
    }  
  if(IsKeyReleased(KEY_V))
    {
      if(height > step)
	height-=step;
    }
  if(IsKeyReleased(KEY_Z))
    {
      width+=step;
    }  
  if(IsKeyReleased(KEY_X))
    {
      height+=step;
    }
 
  if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
      Vector2 pos = GetMousePosition();
      rx = pos.x;
      ry = pos.y;
    }
  if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
    {
      Vector2 pos = GetMousePosition();
      if(pos.x > rx &&
	 pos.y > ry)
	{
	  width = pos.x - rx;
	  height = pos.y - ry;
	}
    }

  if(IsKeyReleased(KEY_Q))
    {
      step+=1;
    }
  if(IsKeyReleased(KEY_E))
    {
      if(step > 2)
	step-=1;
    }

  if(IsKeyReleased(KEY_SPACE))
    {
      if(rect_color.r == MAGENTA.r &&
	 rect_color.g == MAGENTA.g &&
	 rect_color.b == MAGENTA.b &&
	 rect_color.a == MAGENTA.a)
	{
	  rect_color = BLANK;
	}
      else
	{
	  rect_color = MAGENTA;
	}
	 
    }
  
  if(IsKeyReleased(KEY_ENTER))
    {
      //prevent x11 from crushing at this edge case
      if(rx < 0) rx = 0;
      if(ry < 0) ry = 0;
      
      X11Image ximg = take_x11_screenshot((int)rx,
					  (int)ry,
					  width,
					  height);
      save_img(&ximg);      
      SetWindowSize(400, 100);
      SetWindowPosition(before_rect_wpos.x, before_rect_wpos.y);
    }
  
  if(IsKeyReleased(KEY_ESCAPE))
    {
      sc_state = StartMenu;
      SetWindowPosition(before_rect_wpos.x, before_rect_wpos.y);
      SetWindowSize(200, 110);
      SetExitKey(KEY_ESCAPE);
    }
}
void take_fullscreen_pic(void)
{
  Vector2 pos = GetWindowPosition();
  SetWindowSize(1, 1);
  SetWindowPosition(-1, -1);
  WaitTime(1.0);
  
  X11Image ximg = take_x11_screenshot(-1,-1,-1,-1);

  save_img(&ximg);
  SetWindowSize(400, 100);
  SetWindowPosition(pos.x, pos.y);
}
void save_img(X11Image* ximg)
{
  if (!ximg->data)
    {
      fprintf(stderr,"Failed to capture screenshot\n");
      sc_state = StartMenu;
      SetWindowSize(200, 110);
      image_failed = true;
      strcpy(error_message,"Error: X11Image creation failed!");
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
      if(!check_dir_available(dir))
	{
	  sc_state = StartMenu;
	  SetWindowSize(200, 110);
	  image_failed = true;
	  snprintf(error_message, 255, "Error: %s is not available!", dir);
	}
      
      sprintf(full,"%s%s.png",dir,name);
      free(dir);
    }
  else
    {
      if(!check_dir_available(save_dir))
	{
	  sc_state = StartMenu;
	  SetWindowSize(200, 110);
	  image_failed = true;
	  snprintf(error_message, 255, "Error: %s is not available!", save_dir);
	}
      sprintf(full,"%s%s.png",save_dir,name);
    }
  
  
  sprintf(last_save, "#112# %s.png", full);
  last_save[strlen(last_save)+10] = '\0';
  ExportImage(screenshot, full);
  UnloadImage(screenshot);
  sc_state = MessageBox;
}
void draw_rect(void)
{
  DrawRectangle(rx, ry, width, 2, rect_color);
  DrawRectangle(rx, ry+height, width, 2, rect_color);
  DrawRectangle(rx, ry, 2, height, rect_color);
  DrawRectangle(rx+width, ry, 2, height, rect_color);
}
void draw_message_box(void)
{
  if(!image_failed)
    {
      GuiLabel((Rectangle){10,10,180,20}, "Screenshot saved:");
      GuiLabel((Rectangle){10,30,350,40}, last_save);
    }
  else
    {
      GuiLabel((Rectangle){100,30,350,20}, "#113# Image creation failed!");
      GuiLabel((Rectangle){60,30,300,50}, error_message);
    }

  if(GuiButton((Rectangle){160,70,60,20}, "[O]k") ||
     IsKeyPressed(KEY_O))
    {
      SetWindowSize(200, 110);
      sc_state = StartMenu;
      image_failed = false;
    }
}
