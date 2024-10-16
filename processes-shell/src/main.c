#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void interpret(char *line) {
  printf("interpret line: %s", line);
  size_t length = strlen(line);
  // this kills the line break because we hates it
  char *line_copy = malloc(sizeof(char) * --length);
  line_copy = strncpy(line_copy, line, length);
  printf("args:");
  while (line_copy != NULL) {
    char *separated = strsep(&line_copy, " ");
    printf(" [ %s ]", separated);
  }
  printf("\n");
  free(line_copy);
}

void repl(void) {
  size_t line_size = 1024;
  char *line = malloc(sizeof(char) * line_size);
  while (true) {
    printf("wish> ");
    ssize_t bytes_read = getline((char **)&line, &line_size, stdin);
    if (bytes_read == -1) {
      free(line);
      exit(0);
    }
    interpret(line);
  }
}

void batch(const char *name) {
  FILE *fp = fopen(name, "r");
  if (fp == NULL) {
    fprintf(stderr, "wish: could not open file \"%s\"\n", name);
    exit(74);
  }

  size_t line_size = 1024;
  char *line = malloc(sizeof(char) * line_size);
  while (true) {
    ssize_t bytes_read = getline(&line, &line_size, fp);
    if (bytes_read == -1) {
      free(line);
      fclose(fp);
      exit(0);
    }
    interpret(line);
  }
}

int main(int argc, const char *argv[]) {
  switch (argc) {
  case 1:
    repl();
    break;
  case 2:
    batch(argv[1]);
    break;
  default:
    fprintf(stderr, "usage: wish [batch file]\n");
    return 1;
  }
  return 0;
}
