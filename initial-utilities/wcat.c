#include <stdlib.h>
#include <stdio.h>

char* read_file(const char* name) {
	FILE* fd = fopen(name, "r");
	if (fd == NULL) {
		fprintf(stderr, "wcat: cannot open file");
		exit(74);
	}

	fseek(fd, 0L, SEEK_END);
	size_t len = ftell(fd);
	rewind(fd);

	char* buf = (char*)malloc(len);
	if (buf == NULL) {
		fprintf(stderr, "wcat: cannot open file");
		exit(74);
	}
	size_t bytes_read = fread(buf, sizeof(char), len, fd);
	if (bytes_read < len) {
		fprintf(stderr, "wcat: cannot open file");
		exit(74);
	}
	buf[bytes_read] = '\0';

	fclose(fd);
	return buf;
}

int main(int argc, const char* argv[]) {
	for (int  i = 1; i < argc; i++) {
		char* text = read_file(argv[i]);
		printf("%s", text);
		free(text);
	}
	return 0;
}
