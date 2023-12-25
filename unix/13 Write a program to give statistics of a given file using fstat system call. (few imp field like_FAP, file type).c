#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char filename[100];
    int fd;

    printf("Enter the file name: ");
    scanf("%s", filename);

    // Open the file
    fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror("Error in opening file");
        return 1;
    }

    struct stat fileStat;

    // Use fstat system call to get file statistics
    if (fstat(fd, &fileStat) == -1) {
        perror("Error in getting file stats");
        close(fd);
        return 1;
    }

    // File access permissions
    printf("File access permissions: ");
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // File type
    printf("File type: ");
    if (S_ISREG(fileStat.st_mode))
        printf("Regular file\n");
    else if (S_ISDIR(fileStat.st_mode))
        printf("Directory\n");
    else if (S_ISCHR(fileStat.st_mode))
        printf("Character device\n");
    else if (S_ISBLK(fileStat.st_mode))
        printf("Block device\n");
    else if (S_ISFIFO(fileStat.st_mode))
        printf("FIFO/pipe\n");
    else if (S_ISLNK(fileStat.st_mode))
        printf("Symbolic link\n");
    else if (S_ISSOCK(fileStat.st_mode))
        printf("Socket\n");
    else
        printf("Unknown\n");

    // Additional file statistics
    printf("File size: %lld bytes\n", fileStat.st_size);
    printf("Inode number: %ld\n", fileStat.st_ino);
    printf("Number of hard links: %ld\n", fileStat.st_nlink);
    printf("Device ID: %ld\n", fileStat.st_dev);
    printf("User ID of owner: %d\n", fileStat.st_uid);
    printf("Group ID of owner: %d\n", fileStat.st_gid);

    // Close the file
    close(fd);

    return 0;
}
