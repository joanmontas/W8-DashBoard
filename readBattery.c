#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(){

  int fd;
  int length = 1;
  struct stat file_info;
  char* buffer;

  /* Open the file.  */
  fd = open ("/sys/class/power_supply/BAT0/capacity", O_RDONLY);

  /* Get information about the file.  */
  fstat (fd, &file_info);
  length = file_info.st_size;
  /* Make sure the file is an ordinary file.  */
  if (!S_ISREG (file_info.st_mode)) {
    /* It's not, so give up.  */
    close (fd);
    return 1;
  }

  /* Allocate a buffer large enough to hold the file's contents.  */
  buffer = (char*) malloc (length);
  /* Read the file into the buffer.  */
  read (fd, buffer, length);

  /* Finish up.  */
  close (fd);
  printf("%s",buffer);
  return 0;
};

