#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
        int fd, cfd = 0;
        if (argc != 3) {
                printf("Usage: %s source file and string\n", argv[0]);
                return 1;
         }
         fd = open(argv[1], O_APPEND | O_RDWR | O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
         if (fd == -1) {
                   perror("Cannot create or modify file\n");
                   return 1;
         }
         dprintf(fd,"%s", argv[2]);
        cfd = close(fd);
        if (cfd != 0) {
                 perror("Unsucessful closing");
                return 1;
        }

        return 0;

}
