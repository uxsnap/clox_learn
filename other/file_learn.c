#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  const char *fileName = "./test.txt"; 
  const char *someData = "sssasssass";

  FILE *fp = fopen(fileName, "r+");
  fseek(fp, 15, SEEK_SET);
  fwrite(someData, strlen(someData), 1, fp);
  fseek(fp, 0L, SEEK_END);
  fclose(fp);
  return 0;
}