#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf ("Usage: %s some.file\n", argv[0]);
		return 1;
	}

	struct stat stat_buf;
	if (lstat (argv[1], &stat_buf) == -1) {
		perror("Failed to stat");
		return 2;
	}

	printf("Mode: %06o\n", stat_buf.st_mode);
	printf("Size: %llu\n", (unsigned long long)stat_buf.st_size);
	printf("Used space: %llu\n", (unsigned long long)stat_buf.st_blocks * S_BLKSIZE);
	printf("Last status change:       %s", ctime(&stat_buf.st_ctime));
        printf("Last file access:         %s", ctime(&stat_buf.st_atime));
        printf("Last file modification:   %s", ctime(&stat_buf.st_mtime));
	return 0;
}
