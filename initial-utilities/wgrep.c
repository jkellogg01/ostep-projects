#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep_file(FILE *fp, const char *search_term) {
  size_t st_len = strlen(search_term);

  size_t buf_size = 1024;
  char *buf = (char *)malloc(buf_size);
  ssize_t bytes_read = getline(&buf, &buf_size, fp);
  while (bytes_read != -1) {
    for (size_t i = 0; i + st_len < bytes_read; ++i) {
      int cmp = memcmp(buf + i, search_term, st_len);
      if (cmp != 0)
        continue;
      printf("%s", buf);
    }
    bytes_read = getline(&buf, &buf_size, fp);
  }
  free(buf);
  return;
}

int main(int argc, const char *argv[]) {
  if (argc <= 1) {
    printf("wgrep: searchterm [file ...]\n");
    return 1;
  }
  const char *search_term = argv[1];
  if (argc == 2) {
    grep_file(stdin, search_term);
    return 0;
  }
  for (int i = 2; i < argc; ++i) {
    FILE *fp = fopen(argv[i], "r");
    grep_file(fp, search_term);
    fclose(fp);
  }
  return 0;
}
