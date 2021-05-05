#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "HeapStrHeader.h"

#define ROW 1000000
#define COLUMN 128
#define OFFSET 1

int len = 0;
char input[ROW][COLUMN];

int main(){

    int i;
    FILE *fp;
    struct  timeval start;
    struct  timeval end;
    unsigned  long diff;

    gettimeofday(&start,NULL);

    while(fgets(&input[len][0], COLUMN, stdin)){
        len++;
    }

    HeapSort();

    fp = fopen("Hsorted2.txt", "w");
    for(i = 0; i < len; i++){
        fprintf(fp, "%s", input[i]);
    }
    fclose(fp);

    gettimeofday(&end,NULL);
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("execution time : %ld µs\n",diff);

    return 0;
}

void swap(char *a, char *b){

    char temp[COLUMN];

    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);

}

void MaxHeapify(int root, int size){

    int left = 2 * root;
    int right = 2 * root + 1;
    int largest;

    if(left <= size && strcmp(&input[left - OFFSET][0], &input[root - OFFSET][0]) > 0){
        largest = left;
    }
    else{
        largest = root;
    }

    if(right <= size && strcmp(&input[right - OFFSET][0], &input[largest - OFFSET][0]) > 0){
        largest = right;
    }

    if(largest != root){
        swap(&input[largest - OFFSET][0], &input[root - OFFSET][0]);
        MaxHeapify(largest, size);
    }

}

void BuildMaxHeap(){

    int i;

    for(i = len / 2; i >= 1; i--){
        MaxHeapify(i, len);
    }

}

void HeapSort(){

    int i;
    int size = len;
    
    BuildMaxHeap();

    for(i = len; i > 1; i--){
        swap(&input[1 - OFFSET][0], &input[i - OFFSET][0]);
        size--;
        MaxHeapify(1, size);
    }
}