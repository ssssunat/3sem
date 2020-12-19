#include <stdio.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <sys/statvfs.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s some.file\n", argv[0]);
        return 1;
    }
    struct statfs buf;
    if (statvfs(argv[1], &buf) == -1) {
        perror("Failed to statvfs");
        return 1;
    }
    printf("Total: %lu\n", buf.f_frsize * buf.f_blocks);
    printf("Available: %lu\n", buf.f_frsize * buf.f_bavail);
    printf("Used: %lu\n", buf.f_frsize * buf.f_blocks - buf.f_frsize * buf.f_bfree);
    return 0;
}
