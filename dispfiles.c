/*
 * This program displays the names of all files in the current directory.
 */

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

char *trimwhitespace(char *);



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
      char *fname = dir->d_name;

      char cmd[128];
      strcpy(cmd,"file -b \"");
      strcat(cmd,fname);
      strcat(cmd,"\"");
      //printf("%s\n",cmd);
      FILE *in = popen(cmd,"r");
      char buff[512];
      while(fgets(buff, sizeof(buff), in)!=NULL){
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
	      trimwhitespace(imtitle);
	      //puts(imfile);
	    
	      char *datime = strtok(NULL,delimr);
	      trimwhitespace(datime);
	      //puts(datime);

	      char exif_cmd[128];
	      strcpy(exif_cmd,"exiftool ");
	      strcat(exif_cmd,"\"-DateTimeOriginal=");
	      strcat(exif_cmd,datime);
	      strcat(exif_cmd,"\" \"");
	      strcat(exif_cmd,imfile);
	      strcat(exif_cmd,"\"");
	      puts(exif_cmd);
	      system(exif_cmd);
	      system("\\rm -f *_original*");
	    }

	}
      
    }

    closedir(d);
  }

  return(0);
}



char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

