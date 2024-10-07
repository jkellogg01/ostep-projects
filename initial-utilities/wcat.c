#include <stdio.h>
#include <stdlib.h>

void print_file(const char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    printf("wcat: cannot open file\n");
    exit(1);
  }

  char *buf = (char *)malloc(1024);
  char *result = fgets(buf, sizeof(buf), fp);
  while (result != NULL) {
    printf("%s", buf);
    result = fgets(buf, sizeof(buf), fp);
  }
  free(buf);
  fclose(fp);
}

int main(int argc, const char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    print_file(argv[i]);
  }
  return 0;
}
