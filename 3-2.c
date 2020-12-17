#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
	if (argc != 3){
		printf("Usage: %s [source file] [target file]\n", argv[0]);
		return 1;
	}
    struct stat filestat;
    if (lstat(argv[1], &filestat) == -1) {
        perror("Failed to stat");
        return 2;
    }
    if ((filestat.st_mode & S_IFMT) != S_IFREG) {
        printf("Error: Not regular\n");
        return 2;
    }

	int file1_fd = open(argv[1], O_RDONLY);
	if (file1_fd == -1){
		perror("Failed to open source file");
		return 2;
	}
	int file2_fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	if (file2_fd == -1){
		perror("Failed to open target file");
		return 2;
	}
	off_t bytes_read = 0;
    	off_t all_bytes_written = 0;
	while (1){
		char buf[512];
		ssize_t buf_size = pread(file1_fd, buf, sizeof(buf), bytes_read);

		if (buf_size == -1) {
			perror("Failed to read a block");
			close(file1_fd);
			close(file2_fd);
            		return 2;
		}
		if (buf_size == 0){
			break;
		}
       		bytes_read += buf_size;
		size_t local_buf_size = (size_t)buf_size;
		size_t bytes_written = 0;
		while (bytes_written < local_buf_size) {
			ssize_t write_result = pwrite(file2_fd, &buf[bytes_written], local_buf_size - bytes_written, all_bytes_written);

			if (write_result == -1) {
				perror("Failed to write");
				close(file1_fd);
				close(file2_fd);
				return 3;
			}
			bytes_written += (size_t)write_result;
            		all_bytes_written += (off_t)write_result;
		}		
	}
    	fsync(file2_fd);
	close(file1_fd);
	close(file1_fd);
	return 0;
}
