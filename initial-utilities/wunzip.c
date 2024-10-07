#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *name) {
  FILE *fp = fopen(name, "r");
  if (fp == NULL) {
    fprintf(stderr, "wunzip: could not open file\n");
    exit(1);
  }

  fseek(fp, 0L, SEEK_END);
  size_t file_length = ftell(fp);
  rewind(fp);

  char *buffer = (char *)malloc(file_length);
  if (buffer == NULL) {
    fprintf(stderr, "wunzip: could not open file\n");
    exit(1);
  }
  size_t bytes_read = fread(buffer, sizeof(char), file_length, fp);
  if (bytes_read < file_length) {
    fprintf(stderr, "wunzip: could not open file\n");
    exit(1);
  }
  buffer[bytes_read] = '\0';

  fclose(fp);
  return buffer;
}

void decompress(char *source) {
  size_t idx = 0;
  char c = source[idx + 4];
  while (c != '\0') {
    uint32_t times = 0;
    for (int i = idx; i < idx + 4; i++) {
      int add = (int)source[i];
      for (int j = 0; j < i - idx; j++) {
        add *= 256;
      }
      times += add;
    }
    for (int i = 0; i < times; i++) {
      printf("%c", c);
    }
    idx += 5;
    c = source[idx + 4];
  }
}

int main(int argc, const char *argv[]) {
  if (argc <= 1) {
    fprintf(stderr, "wunzip: file1 [file2 ...]\n");
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    char *data = read_file(argv[i]);
    decompress(data);
    free(data);
  }
  return 0;
}
