#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
  printf("The c file will be going through the directory it is in.\n");

  DIR * directory;
  directory = opendir(".");
  printf("Error if any: %i: %s\n", errno, strerror(errno));
  struct dirent *currentFile;
  int counter = 0;
  printf("\n");
  while (currentFile != NULL) {
    currentFile = readdir(directory);
    if (currentFile != NULL) {
      printf("Returning metadata on file number %i:\n", counter);
      printf("Error, if any: %i: %s\n", errno, strerror(errno));
      printf("File name: %s\n", currentFile->d_name);
      struct stat filestat;
      stat(currentFile->d_name, &filestat);
      printf("File size: %li bytes\n", filestat.st_size);
      char filetype[25];
      if (currentFile->d_type == DT_REG) {
        strcpy(filetype, "Normal file");
      }
      else if (currentFile->d_type == DT_DIR) {
        strcpy(filetype, "Directory");
      }
      else {
        strcpy(filetype, "other");
      }
      printf("File type: %d: %s\n", currentFile->d_type, filetype);
      counter++;
      printf("\n");
    }
    else {
      printf("We have arrived at the end of the directory.\n");
    }
  }
}
