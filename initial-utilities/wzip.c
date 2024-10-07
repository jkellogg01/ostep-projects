#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char* read_file(const char* name) {
	FILE* fp = fopen(name, "r");
	if (fp == NULL) {
		printf("wzip: could not open file\n");
		exit(1);
	}

	fseek(fp, 0L, SEEK_END);
	size_t file_len = ftell(fp);
	rewind(fp);

	char* buf = (char*)malloc(file_len);
	if (buf == NULL) {
		printf("wzip: could not open file\n");
		exit(1);
	}
	size_t bytes_read = fread(buf, sizeof(char), file_len, fp);
	if (bytes_read < file_len) {
		printf("wzip: could not open file\n");
		exit(1);
	}
	buf[bytes_read] = '\0';

	fclose(fp);
	return buf;
}

void compress_to(char* data, FILE* stream) {
	size_t idx = 0;
	char c = data[idx++];
	int32_t run = 1;
	while (c != '\0') {
		if (c == data[idx]) {
			run += 1;
			c = data[idx++];
			continue;
		}
		size_t n;
		n = fwrite(&run, 1, 4, stream);
		if (n < 4) {
			fprintf(stderr, "failed to write 4-byte binary int [n=%d]\n", (int)n);
			exit(1);
		}
		n = fwrite(&c, sizeof(char), 1, stream);
		if (n < 1) {
			fprintf(stderr, "failed to write ascii character [n=%d]\n", (int)n);
			exit(1);
		}
		run = 1;
		c = data[idx++];
	}
}

int main(int argc, const char* argv[]) {
	if (argc <= 1) {
		printf("wzip: file1 [file2 ...]\n");
		return 1;
	}
	for (size_t i = 1; i < argc; i++) {
		char* data = read_file(argv[i]);
		compress_to(data, stdout);
		free(data);
	}
	return 0;
}
