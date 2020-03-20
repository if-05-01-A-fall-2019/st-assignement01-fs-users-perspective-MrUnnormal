#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char path[255];
    strcpy(path, ".");
    DIR* dir = opendir(path);
    struct dirent* dir_entry;
    struct stat dir_attributes;
    while((dir_entry = readdir(dir))) {
        if(dir_entry->d_name[0] != '.') {
            strcpy(path, dir_entry->d_name);
            lstat(path, &dir_attributes);
            switch (dir_attributes.st_mode & S_IFMT) {
                case S_IFREG:  
                    printf("Regular file");
                    break;
                case S_IFDIR:
                    printf("Directory");
                    break;
                case S_IFCHR:        
                    printf("Character Device");
                    break;
                case S_IFBLK:        
                    printf("Block device");
                    break;
                case S_IFLNK: 
                    printf("Symlink");
                    break;
                case S_IFIFO: 
                    printf("Pipe");    
                    break;
                case S_IFSOCK:
                    printf("Socket");
                    break;
                default:
                    printf("? - Unknown");
            }
            printf(" ");
            printf((dir_attributes.st_mode & S_IRUSR) ? "r" : "-");
            printf((dir_attributes.st_mode & S_IWUSR) ? "w" : "-");
            printf((dir_attributes.st_mode & S_IXUSR) ? "x" : "-");
            printf((dir_attributes.st_mode & S_IRGRP) ? "r" : "-");
            printf((dir_attributes.st_mode & S_IWGRP) ? "w" : "-");
            printf((dir_attributes.st_mode & S_IXGRP) ? "x" : "-");
            printf((dir_attributes.st_mode & S_IROTH) ? "r" : "-");
            printf((dir_attributes.st_mode & S_IWOTH) ? "w" : "-");
            printf((dir_attributes.st_mode & S_IXOTH) ? "x" : "-");
            printf("%5d", dir_attributes.st_uid);
            printf(" %5d", dir_attributes.st_gid);
            printf(" %9ld ", dir_attributes.st_size);
            printf(" %s ", ctime(&dir_attributes.st_mtime));
            printf("%s\n", dir_entry->d_name);
        }
    }
}