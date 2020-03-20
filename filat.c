#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    struct stat attributes;
    const char* path = argv[1];
    if(path == 0) {
        printf("No path specified\n");
        return -1;
    }
    int lstat_return = lstat(path, &attributes);
    if(lstat_return < 0) {
        printf("Can not stat file: %s", path);
        return -1;
    }
    printf("Attributes of file: %s", path);
    printf("File type: ");
    switch (attributes.st_mode & S_IFMT) {
        case S_IFREG:  
            printf("Regular file\n");
            break;
        case S_IFDIR:
            printf("Directory\n");
            break;
        case S_IFCHR:        
            printf("Character Device\n");
            break;
        case S_IFBLK:        
            printf("Block device\n");
            break;
        case S_IFLNK: 
            printf("Symlink\n");
            break;
        case S_IFIFO: 
            printf("Pipe\n");    
            break;
        case S_IFSOCK:
            printf("Socket\n");
            break;
        default:
            printf("? - Unknown\n");
    }
    printf("Access privileges: ");
    printf((S_ISDIR(attributes.st_mode)) ? "d" : "-");
    printf((attributes.st_mode & S_IRUSR) ? "r" : "-");
    printf((attributes.st_mode & S_IWUSR) ? "w" : "-");
    printf((attributes.st_mode & S_IXUSR) ? "x" : "-");
    printf((attributes.st_mode & S_IRGRP) ? "r" : "-");
    printf((attributes.st_mode & S_IWGRP) ? "w" : "-");
    printf((attributes.st_mode & S_IXGRP) ? "x" : "-");
    printf((attributes.st_mode & S_IROTH) ? "r" : "-");
    printf((attributes.st_mode & S_IWOTH) ? "w" : "-");
    printf((attributes.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    printf("inode-NUmber: %li\n", attributes.st_ino);
    printf("Device numbers: %li\n", attributes.st_dev);
    printf("Links count %li\n", attributes.st_nlink);
    printf("UID: %d\n", attributes.st_uid);
    printf("GID: %d\n", attributes.st_gid);
    printf("Size: %ld\n", attributes.st_size);
    printf("Size: %ld\n", attributes.st_size);
    printf("Last access: %s", ctime(&attributes.st_atime));
    printf("Last modification: %s", ctime(&attributes.st_mtime));
    printf("Last inode change: %s", ctime(&attributes.st_ctime));
    return 0;
}
