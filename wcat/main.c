#include <stdio.h>
#include <stdlib.h>

void cat_file(const char* name) {
	FILE* fp = fopen(name, "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file: %s\n", name);
		exit(1);
	}

	fseek(fp, 0L, SEEK_END);
	size_t len = ftell(fp);
	rewind(fp);

	char* buffer = (char*)malloc(len + 1);
	if (buffer == NULL) {
		fprintf(stderr, "not enough memory to read file: %s\n", name);
		exit(1);
	}
	size_t bytesRead = fread(buffer, sizeof(char), len, fp);
	if (bytesRead < len) {
		fprintf(stderr, "could not read file: %s\n", name);
		exit(1);
	}
	buffer[bytesRead] = '\0';

	fclose(fp);
	printf("%s", buffer);
	return;
}

int main(int argc, const char* argv[]) {
	if (argc <= 1) {
		return 0;
	}
	for (int i = 1; i < argc; ++i) {
		cat_file(argv[i]);
	}
	return 0;
}
