#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv){

    FILE *fp;
    char *tmpbuf;
    char *buf;
    int i;
    unsigned int fileSize;
    unsigned int readSize;

    //open file
    fp = fopen(argv[1], "r+"); //要用r+才讀得到東西
    if(fp == NULL){
        fprintf(stderr, "open error\n");
    }

    //get file size
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    tmpbuf = (char *)malloc(fileSize + 1);
    buf = (char *)malloc(fileSize + 1);
    if(tmpbuf == NULL || buf == NULL){
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);

    //read file to tmpbuf
    readSize = fread(tmpbuf, sizeof(char), fileSize, fp);
    tmpbuf[readSize] = '\0';
    if(readSize == 0){
        fprintf(stderr, "read error\n");
    }

    //reverse tmpbuf to buf
    for(i = 0; i < readSize; i++){
        buf[i] = tmpbuf[readSize - 1 - i];
    }
    buf[readSize] = '\0';

    //write buf to file
    fseek(fp, 0, SEEK_SET); //回到檔案開頭重新寫入，沒有的話會接在後面印
    fwrite(buf, sizeof(char), readSize, fp);

    fclose(fp);

    return 0;
}