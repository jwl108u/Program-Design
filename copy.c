#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){

    int fd1;
    int fd2;
    unsigned int fileSize;
    unsigned int readSize;
    char *buf;

    //open file
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); //如果有O_CREAT就要指定mode
    if(fd1 < 0 || fd2 < 0){
        fprintf(stderr, "open error\n");
    }

    //get file size
    fileSize = lseek(fd1, 0, SEEK_END);
    buf = (char *)malloc(fileSize + 1);
    if(buf == NULL){
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    lseek(fd1, 0, SEEK_SET);

    //read file1 to buffer
    readSize = read(fd1, buf, fileSize);
    buf[readSize] = '\0';

    //write buffer to file2
    write(fd2, buf, readSize);

    close(fd1);
    close(fd2);

    return 0;
}