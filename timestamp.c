/*
 * This program displays the names of all files in the current directory.
 */

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

void usage();

int main( int argc, char *argv[] )
{

  if (argc > 1)
    {
      if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0)
	{
	  usage();
	  return;
	}
    }
  
  DIR *d;
  struct dirent *dir;
  d = opendir(".");

  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      //printf("%s\n", dir->d_name);
      char *fname = dir->d_name;

      char cmd[128];
      strcpy(cmd,"file -b \"");
      strcat(cmd,fname);
      strcat(cmd,"\"");
      //printf("%s\n",cmd);
      FILE *in = popen(cmd,"r");
      char buff[128];
      while(fgets(buff, sizeof(buff), in) != NULL){
	//printf("%s", buff);
      }
      pclose(in);

      if (strstr(buff,"image data") != NULL) // only list image files
	{
	  //printf("%s\n", fname);
	  //printf("%s", buff);

	  char deliml[] = "(";
	  char delimr[] = ")";

	  if (strstr(fname,deliml) != NULL && strstr(fname,delimr) != NULL) //file has correct format
	    {
	      
	      char *p = strstr(fname,".");
	      char *fext = ++p;
	      //printf("%s\n",fext);

	      char imfile[128];
	      strcpy(imfile,fname);
	      //puts(imfile);
	      char *imtitle = strtok(fname,deliml);
	      //puts(imfile);
	    
	      char *datime = strtok(NULL,delimr);
	      //puts(datime);

	      char exif_cmd[128];
	      strcpy(exif_cmd,"exiftool ");
	      strcat(exif_cmd,"\"-DateTimeOriginal=");
	      strcat(exif_cmd,datime);
	      strcat(exif_cmd,"\" ");
	      strcat(exif_cmd,"-overwrite_original \"");
	      strcat(exif_cmd,imfile);
	      strcat(exif_cmd,"\"");
	      puts(exif_cmd);
	      system(exif_cmd);
	    }

	}
      
    }

    closedir(d);
  }

  return(0);
}

void usage()
{
  printf("Usage: timestamp\n\
Updates picture metadata with date and time of when it was taken.\n\
The function reads title, date and time from the file name.\n\
Format should be:\n\
<title> (<date> <time>).ext\n\
Ex:\n\
title (2015:08:20 10:15:0).jpg\n");
}

