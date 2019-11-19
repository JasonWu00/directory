#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int iterateThroughDirectory(struct dirent *currentFile, DIR *directory) {
  int counter = 0;
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
      return 0;
    }
  }
}

int main(int argc, char *argv[]) {
  printf("C file opened. Please enter a directory you wish to return metadata on.\n");
  printf("To scan the current working directory, press enter without typing anything.\n");
  char direc[100];
  fgets(direc, 100, stdin);
  DIR * directory;

  char *position;
  if ((position=strchr(direc, '\n')) != NULL) {
    *position = '\0';
  }

  if (strcmp(direc, "") == 0) {
    printf("\nOpening current working directory\n");
    directory = opendir(".");
  }
  else {
    printf("\nOpening directory with the path %s\n", direc);
    directory = opendir(direc);
  }
  if (errno != 0) {
    printf("Error for opening the directory: %i: %s. Exiting program.\n", errno, strerror(errno));
    return 0;
  }
  else {
    printf("No error encountered opening the directory\n");
  }
  struct dirent *currentFile;
  printf("\n");

  iterateThroughDirectory(currentFile, directory);
}
