#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc > 2) {
		printf("Usage: %s", argv[1]);
		return 1;
	}

	DIR *dir;
	struct stat file;
	
	const char *path;
	
	if (argc == 2) {
		path = argv[1];
	} else {
		path = ".";
	}
	struct dirent *d_stream = opendir(path);
	if (d_stream == NULL) {
		 		perror("Failed to opendir");
        return 2;
	}
	
	while ((d_stream = readdir(dir)) != NULL) {
		printf("File type:\t");
		if ((d_stream->d_type) == DT_UNKNOWN) {
			if (lstat(d_stream->d_name, &file) < 0) {
					perror("Failed to stat");
          return 2;
			 }
			switch (file.st_mode & S_IFMT) {
				case S_IFBLK: printf("Block device"); break;
				case S_IFCHR: printf("Character device"); break;
				case S_IFDIR: printf("Directory"); break;
				case S_IFIFO: printf("Fifo/pipe"); break;
				case S_IFLNK: printf("Symbolyc link"); break;
				case S_IFREG: printf("Regular file"); break;
				case S_IFSOCK: printf("Socket"); break;
				default: printf("Unknown?"); break;
			}
		} else {
			switch (d_stream->d_type) {
				case DT_BLK: printf("Block device"); break;
				case DT_DIR: printf("Directory"); break;
				case DT_CHR: printf("Character device"); break;
				case DT_FIFO: printf("Fifo/pipe"); break;
				case DT_LNK: printf("Symbolic link"); break;
				case DT_REG: printf("Regular file"); break;
				case DT_SOCK: printf("Socket");
			}
		}

		printf("Name: %s \n", d_stream->d_name);
	}
	closedir(dir);
	return 0;
}
