#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "overwrite.h"

#define ASCII_MAX 255 - ' '

int isRegularFile(const char *path);
long int findSize(char* fileName);

int meowDirectoryOverride(char* dirPath, char* overwriteStr) {
  return overwriteDirectory(dirPath, "meow");
}

//returns the amount of bytes written
int overwriteDirectory(char* dirPath, char* overwriteStr) {
  DIR *d;
  struct dirent *dir;
  int bytesWritten = 0;

  d = opendir(dirPath);


  if(d) {
    while ((dir = readdir(d)) != NULL) {
      char* name = dir->d_name;
      char path[255] = "";
      strcat(path, dirPath);
      strcat(path, name);
      if(strcmp(name, ".") && strcmp(name, "..")) {
        printf("%s",path);
        if(isRegularFile(path)) {
          printf(" FILE\n");
          int written = overwriteFile(path, overwriteStr);
          if(written > 0)
            bytesWritten += written;
        }
        else {
          printf(" DIR\n");
          strcat(path, "/");
          bytesWritten += overwriteDirectory(path, overwriteStr);
        }
      }
    }
    closedir(d);
  }

  return bytesWritten;
}

int isRegularFile(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

//returns the amount of bytes written, -1 if the file couldn't be opened
int overwriteFile(char* filePath, char* overwriteStr) {
  FILE *fp;
  long writeSize = findSize(filePath);

  if(writeSize == -1)
    return -1;

  fp = fopen(filePath, "w");
  int written = 0;

  while(writeSize > 0 ) {
    int writeAmount = strlen(overwriteStr) > writeSize ? writeSize : strlen(overwriteStr);
    written += fwrite(overwriteStr, 1, writeAmount, fp);
    writeSize -= writeAmount;
  }

  fclose(fp);
  return written;
}

long int findSize(char* fileName) {
    FILE* fp = fopen(fileName, "r");

    if (fp == NULL)
        return -1;

    fseek(fp, 0, SEEK_END);
    long int res = ftell(fp);
    fclose(fp);

    return res;
}

void asciiCharacters(char** str) {
  *str = malloc(ASCII_MAX+1);

  for (int i = 0; i < ASCII_MAX; ++i)
    (*str)[i] = ' ' + i;
  (*str)[ASCII_MAX] = 0;
}
