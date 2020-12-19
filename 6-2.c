        
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
        struct stat file;
        const char *path;

        if (argc == 2) {
                path = argv[1];
        } else {
                path = ".";
        }
        DIR *dir = opendir(path);
        if (dir == NULL) {
                perror("Failed to opendir");
                return 2;
        }
        struct dirent *str;
        int fd = dirfd(dir);
        printf("File type       File name");
        while ((str = readdir(dir)) != NULL) {
                if ((str->d_type) == DT_UNKNOWN) {
                        if (fstatat(fd, str->d_name, &file, 0) < 0) {
                                perror("Failed to stat");
                                return 2;
                        }
                        switch (file.st_mode & S_IFMT) {
                                case S_IFBLK: printf("Block device      "); break;
                                case S_IFCHR: printf("Character device  "); break;
                                case S_IFDIR: printf("Directory         "); break;
                                case S_IFIFO: printf("Fifo/pipe         "); break;
                                case S_IFLNK: printf("Symbolyc link     "); break;
                                case S_IFREG: printf("Regular file      "); break;
                                case S_IFSOCK: printf("Socket   "); break;
                                default: printf("Unknown?       "); break;
                        }
                } else {
                        switch (str->d_type) {
                                case DT_BLK: printf("Block device       "); break;
                                case DT_DIR: printf("Directory  "); break;
                                case DT_CHR: printf("Character device   "); break;
                                case DT_FIFO: printf("Fifo/pipe         "); break;
                                case DT_LNK: printf("Symbolic link      "); break;
                                case DT_REG: printf("Regular file       "); break;
                                case DT_SOCK: printf("Socket    ");
                        }
                }
                printf("Name: %s \n", str->d_name);
        }
        close(fd);
        closedir(dir);
        return 0;
}
