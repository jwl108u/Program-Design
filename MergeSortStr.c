#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "MergeStrHeader.h"

#define ROW 1000000
#define COLUMN 128

char input[ROW][COLUMN];
char subleft[ROW / 2][COLUMN];
char subright[ROW / 2][COLUMN];

int main(){

    int i;
    int len = 0;
    FILE *fp;
    struct  timeval start;
    struct  timeval end;
    unsigned  long diff;

    gettimeofday(&start,NULL);

    while(fgets(&input[len][0], COLUMN, stdin)){
        len++;
    }

    MergeSort(0, len - 1);

    fp = fopen("Msorted2.txt", "w");
    for(i = 0; i < len; i++){
        fprintf(fp, "%s", input[i]);
    }
    fclose(fp);

    gettimeofday(&end,NULL);
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("execution time : %ld µs\n",diff);

    return 0;
}

void Merge(int head, int mid, int tail){

    int i;
    int j;
    int k = head;
    int Llen = mid - head + 1;
    int Rlen = tail - mid;
    
    for(i = 0; i < Llen; i++){
        strcpy(&subleft[i][0], &input[head + i][0]);
    }
    for(j = 0; j < Rlen; j++){
        strcpy(&subright[j][0], &input[mid + 1 + j][0]);
    }

    i = 0;
    j = 0;

    while((i < Llen) && (j < Rlen)){
        if(strcmp(&subleft[i][0], &subright[j][0]) < 0){
            strcpy(&input[k][0], &subleft[i][0]);
            i++;
        }
        else{
            strcpy(&input[k][0], &subright[j][0]);
            j++;
        }
        k++;
    }

    while(i < Llen){
        strcpy(&input[k][0], &subleft[i][0]);
        i++;
        k++;
    }
    while(j < Rlen){
        strcpy(&input[k][0], &subright[j][0]);
        j++;
        k++;
    }
}

void MergeSort(int head, int tail){

    int mid;

    if(head < tail){

        mid = (head + tail) / 2;

        MergeSort(head, mid);
        MergeSort(mid + 1, tail);

        Merge(head, mid, tail);

    }
}