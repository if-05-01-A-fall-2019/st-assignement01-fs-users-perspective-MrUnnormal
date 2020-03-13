#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    const int MAX_BUFFER_LENGTH = 1024;
    const char* source = argv[1];
    const char* destination = argv[2];
    //printf("Source: %s\n", source);
    //printf("Destination: %s\n", destination);
    printf("Copying %s into %s...\n", source, destination);
    int fd_source = open(source, O_RDONLY);
    if(fd_source < 0) {
        printf("Unable to open file: %s\n", source);
        return -1;
    }
    char buffer[MAX_BUFFER_LENGTH];
    int source_length = read(fd_source, buffer, MAX_BUFFER_LENGTH);
    if(source_length < 0) {
        printf("Unable to read from file: %s\n", source);
        return -1;
    }                                      //read-    //writepermission
    int fd_destination = creat(destination, S_IRUSR | S_IWUSR);
    write(fd_destination, buffer, source_length);
    printf("Finished copying %s into %s\n", source, destination);
    return 0;
}