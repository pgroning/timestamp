/* Stamp pictures with date and time of when it was taken */

#include <stdio.h>
#include <string.h>
//#include <ctype.h>

void usage();
char *trimwhitespace(char *);


int main( int argc, char *argv[] )
{
  int i;
  char *file_name, line[128], *s, *datime;
  FILE *file;

  if (argc > 1)
    {
      if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0)
	{
	  usage();
	  return;
	}
    }

  file_name = "timestamp.txt";
  file = fopen(file_name,"r"); // read mode

  if( file == NULL )
    {
      perror("Error while opening the file timestamp.txt\n");
      return;
    }
  printf("Reading %s\n",file_name);

  while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
    {
      //if (strcmp(line, "")) // string is empty
	//continue;

      //fputs ( line, stdout ); /* write the line */

      char delim[] = "\"";
      
      char *imfile = strtok(line,delim);
      trimwhitespace(imfile);
      
      char *datime = strtok(NULL,delim);
      trimwhitespace(datime);

      //printf("%s len=%d\n",datime,(int) strlen(datime));

      char exif_cmd[128];
      strcpy(exif_cmd,"exiftool ");
      strcat(exif_cmd,"\"-DateTimeOriginal=");
      strcat(exif_cmd,datime);
      strcat(exif_cmd,"\" \"");
      strcat(exif_cmd,imfile);
      strcat(exif_cmd,"\"");

      printf("%s\n",exif_cmd);
      system(exif_cmd);
    }

  fclose(file);
  return 0;
}


void usage()
{
  printf("Usage: timestamp\n\
Updates picture metadata with date and time of when it was taken.\n\
Reads filename, date and time from a file named timestamp.txt\n\
Format should be:\n\
<filename> \"<date> <time>\"\n\
Ex:\n\
file1.jpg \"2015:08:20 10:15:0\"\n\
file2.jpg \"2015:08:26 11:33:3\"\n\
...\n");
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
