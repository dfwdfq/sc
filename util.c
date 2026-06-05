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

