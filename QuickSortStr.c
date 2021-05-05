#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "QuickStrHeader.h"

#define ROW 1000000
#define COLUMN 128

char input[ROW][COLUMN];

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

    QuickSort(0, len - 1);

    fp = fopen("Qsorted2.txt", "w");
    for(i = 0; i < len; i++){
        fprintf(fp, "%s", input[i]);
    }
    fclose(fp);

    gettimeofday(&end,NULL);
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("execution time : %ld µs\n",diff);

    return 0;
}

void SWAP(char *a, char *b){

    char temp[COLUMN];

    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);

}

int partition(int left, int right){

    int i = left - 1;
    int j;

    for(j = left; j < right; j++){
        if(strcmp(&input[j][0], &input[right][0]) <= 0){
            i++;
            SWAP(&input[i][0], &input[j][0]);
        }
    }

    SWAP(&input[i + 1][0], &input[right][0]);

    return i + 1;

}

void QuickSort(int left, int right){

    int q;

    if(left < right){
        q = partition(left, right);
        QuickSort(left, q - 1);
        QuickSort(q + 1, right);
    }

}