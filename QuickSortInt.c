#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "QuickIntHeader.h"

#define SIZE 1000000

int main(){

    int i;
    int len = 0;
    int input[SIZE];
    FILE *fp;
    struct  timeval start;
    struct  timeval end;
    unsigned  long diff;

    gettimeofday(&start,NULL);

    while(scanf("%d", &input[len]) != EOF){
        len++;
    }

    QuickSort(input, 0, len - 1);

    fp = fopen("Qsorted1.txt", "w");
    for(i = 0; i < len; i++){
        fprintf(fp, "%d\n", input[i]);
    }
    fclose(fp);

    gettimeofday(&end,NULL);
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("execution time : %ld µs\n",diff);

    return 0;
}

void SWAP(int *a, int *b){

    int temp;

    temp = *a;
    *a = *b;
    *b = temp;

}

int partition(int *input, int left, int right){

    int i = left - 1;
    int j;

    for(j = left; j < right; j++){
        if(input[j] <= input[right]){
            i++;
            SWAP(&input[i], &input[j]);
        }
    }

    SWAP(&input[i + 1], &input[right]);

    return i + 1;

}

void QuickSort(int *input, int left, int right){

    int q;

    if(left < right){
        q = partition(input, left, right);
        QuickSort(input, left, q - 1);
        QuickSort(input, q + 1, right);
    }

}