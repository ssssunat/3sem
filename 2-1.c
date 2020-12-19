#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
        if (argc != 3) {
                printf ("Incorrect Usage");
                return 1;
        }
        int fd = open(argv[1], O_APPEND | O_RDWR | O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);//open  превращает имя файла в дескриптор файла или -1 если произошла ошибка
        if (fd == -1) {
                perror("Cannot create or modify file\n");
                return 1;
         }
        int size = strlen(argv[2]);
        int cnt = 0;
        while(size > cnt){
                ssize_t bytes = write(fd, argv[2], size);//В случае успеха возвращается количество записанных байтов, В случае ошибки возвращается -1
                if(bytes == -1){
                        perror("Failed to write:");
                        close(fd);
                        return 1;
                }
                cnt += bytes;
        }
        close(fd);
        return 0;

}

