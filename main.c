#include"startw.h"
int main(void)
{
  StartwResult res = startw_run();
  switch(res)
    {
    case FullscreenMode:
      break;
    case RectangleMode:
      break;
    case ConfigMode:
      break;
    }
  
  return 0;
}
