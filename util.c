#include"sc.h"


void get_file_name(char* output)
{
  //https://stackoverflow.com/questions/5141960/get-the-current-time-in-c#5142028
  time_t rawtime;
  struct tm * timeinfo;
    
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  sprintf(output, "screenshot_%d%d%d%d%d%d", timeinfo->tm_mday,
	  timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
	  timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
char* expand_homedir(char* path)
{
  const char* home = getenv("HOME");
  if(!home)
    {
      fprintf(stderr,"sc error: failed to get $HOME!");
      return NULL;
    }

  size_t len = strlen(home) + strlen(path+1) + 2;  
  char* res = malloc(len);
  if(!res)
    {
      perror("malloc");
      return NULL;
    }
  sprintf(res, "%s%s/",home,path+1);
  return res;
}
