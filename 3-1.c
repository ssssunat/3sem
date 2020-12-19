#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: %s source file target file\n", argv[0]);
		return 1;
	}

        struct stat stat_file;
        if (lstat(argv[1], &stat_file) == -1) {
                perror("Failed to stat");
                return 2;
        }
        if ((stat_file.st_mode & S_IFMT) != S_IFREG) {
                printf("Error: Not regular\n");
                return 2;
        }
        int file1fd = open(argv[1], O_RDONLY);
        if (file1fd == -1) {
                perror("Failed to open source file");
                return 2;
        }
        int file2fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        if (file2fd == -1) {
                perror("Failed to open target file");
                return 2;
        }

        while (1) {
                char buf[512];
                ssize_t bufsize = read(file1fd, buf, sizeof(buf));

                if (bufsize == -1) {
                        perror("Failed to read a block");
                        close(file1fd);
                        close(file2fd);
                        return 2;
                }
                if (bufsize == 0) {
                        break;
                }
                size_t size = (size_t)bufsize;
                size_t bwritten = 0;
                while (size > bwritten) {
                        ssize_t write_result = write(file2fd, &buf[bwritten], size - bwritten);
                        if (write_result == -1) {
                                perror("Failed to write");
                                close(file1fd);
                                close(file2fd);
                                return 3;
                        }
                        bwritten += (size_t)write_result;
                }
        }
        fsync(file2fd);
        close(file1fd);
        close(file2fd);
        return 0;
}
   
