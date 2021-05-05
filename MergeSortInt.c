#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "MergeIntHeader.h"

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

    MergeSort(input, 0, len - 1);

    fp = fopen("Msorted1.txt", "w");
    for(i = 0; i < len; i++){
        fprintf(fp, "%d\n", input[i]);
    }
    fclose(fp);

    gettimeofday(&end,NULL);
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("execution time : %ld µs\n",diff);

    return 0;
}

void Merge(int *input, int head, int mid, int tail){

    int i;
    int j;
    int k = head;
    int Llen = mid - head + 1;
    int Rlen = tail - mid;
    int subleft[Llen];
    int subright[Rlen];
    
    for(i = 0; i < Llen; i++){
        subleft[i] = input[head + i];
    }
    for(j = 0; j < Rlen; j++){
        subright[j] = input[mid + 1 + j];
    }

    i = 0;
    j = 0;

    while((i < Llen) && (j < Rlen)){
        if(subleft[i] < subright[j]){
            input[k] = subleft[i];
            i++;
        }
        else{
            input[k] = subright[j];
            j++;
        }
        k++;
    }

    while(i < Llen){
        input[k] = subleft[i];
        i++;
        k++;
    }
    while(j < Rlen){
        input[k] = subright[j];
        j++;
        k++;
    }
}

void MergeSort(int *input, int head, int tail){

    int mid;

    if(head < tail){

        mid = (head + tail) / 2;

        MergeSort(input, head, mid);
        MergeSort(input, mid + 1, tail);

        Merge(input, head, mid, tail);

    }
}