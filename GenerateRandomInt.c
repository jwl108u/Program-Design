#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000

int main(){

    int i;
    FILE * fp;

    fp = fopen("dataset1.txt", "w");

    srand(time(NULL));

    for(i = 0; i < SIZE; i++){
        fprintf(fp, "%d\n", rand());
    }

    fclose(fp);

    return 0;

}