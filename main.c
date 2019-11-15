#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main() {
  printf("The c file will be going through the directory it is in.\n");

  DIR * directory;
  directory = opendir("/mnt/c/Users/jason/Desktop/[DATA EXPUNGED 2]/WoRk/Systems/directory");
  printf("Error if any: %i: %s\n", errno, strerror(errno));
  struct dirent *currentFile;
  int counter = 0;
  printf("\n");
  while (currentFile != NULL) {
    currentFile = readdir(directory);
    if (currentFile != NULL) {
      printf("Returning metadata on file number %i:\n", counter);
      printf("File name: %s\n", currentFile->d_name);
      counter++;
      printf("\n");
    }
    else {
      printf("We have arrived at the end of the directory.\n");
    }
  }
}
