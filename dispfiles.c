/*
 * This program displays the names of all files in the current directory.
 */

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

int main(void)
{
  DIR           *d;
  struct dirent *dir;
  d = opendir(".");
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      //printf("%s\n", dir->d_name);

      char cmd[128];
      strcpy(cmd,"file -b \"");
      strcat(cmd,dir->d_name);
      strcat(cmd,"\"");
      //printf("%s\n",cmd);
      FILE *in = popen(cmd,"r");
      char buff[512];
      while(fgets(buff, sizeof(buff), in)!=NULL){
	//printf("%s", buff);
      }
      pclose(in);

      if (strstr(buff,"image data") != NULL)
	{
	  printf("%s\n", dir->d_name);
	  printf("%s", buff);
	}
      
    }

    closedir(d);
  }

  return(0);
}
