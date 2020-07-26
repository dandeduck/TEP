#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "overwrite.h"

#define ASCII_MAX 255 - ' '

int tryToOverwriteObject(char* dirPath, char* name, char* overwriteStr);
int overwriteObject(char* path, char* overwriteStr);
int isRegularDir(char* name);
void toPath(char* dir, char* name, char** path);
int isFile(const char *path);
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
    while ((dir = readdir(d)) != NULL)
      bytesWritten += tryToOverwriteObject(dirPath, dir->d_name, overwriteStr);
    closedir(d);
  }

  return bytesWritten;
}

int tryToOverwriteObject(char* dirPath, char* name, char* overwriteStr) {
  char* path;
  toPath(dirPath, name, &path);

  if(isRegularDir(name))
    return overwriteObject(path, overwriteStr);

  free(path);
  return 0;
}

int overwriteObject(char* path, char* overwriteStr) {
  if(isFile(path))
    return overwriteFile(path, overwriteStr);
  else {
    strcat(path, "/");
    return overwriteDirectory(path, overwriteStr);
  }
}

int isRegularDir(char* name) {
  return strcmp(name, ".") && strcmp(name, "..");
}

void toPath(char* dir, char* name, char** path) {
  *path = malloc(strlen(dir)+strlen(name)+2);
  memset(*path,0 , strlen(*path));
  strcat(*path, dir);
  strcat(*path, name);
}

int isFile(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

//returns the amount of bytes written
int overwriteFile(char* filePath, char* overwriteStr) {
  FILE *fp;
  long writeSize = findSize(filePath);
  int written = 0;

  fp = fopen(filePath, "w");

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
