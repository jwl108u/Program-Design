#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "HeapIntHeader.h"

#define SIZE 1000000
#define OFFSET 1

int len = 0;
int input[SIZE];

int main(){

    int i;
    FILE *fp;
    struct  timeval start;
    struct  timeval end;
    unsigned  long diff;

    gettimeofday(&start,NULL);

    while(scanf("%d", &input[len]) != EOF){
        len++;
    }

    HeapSort();

    fp = fopen("Hsorted1.txt", "w");
    for(i = 0; i < len; i++){
        fprintf(fp, "%d\n", input[i]);
    }
    fclose(fp);

    gettimeofday(&end,NULL);
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("execution time : %ld µs\n",diff);

    return 0;
}

void swap(int *a, int *b){

    int temp;

    temp = *a;
    *a = *b;
    *b = temp;

}

void MaxHeapify(int root, int size){

    int left = 2 * root;
    int right = 2 * root + 1;
    int largest;

    if(left <= size && input[left - OFFSET] > input[root - OFFSET]){
        largest = left;
    }
    else{
        largest = root;
    }

    if(right <= size && input[right - OFFSET] > input[largest - OFFSET]){
        largest = right;
    }

    if(largest != root){
        swap(&input[largest - OFFSET], &input[root - OFFSET]);
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
        swap(&input[1 - OFFSET], &input[i - OFFSET]);
        size--;
        MaxHeapify(1, size);
    }
}