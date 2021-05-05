#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000
#define LEN 100

int main(){

    int i;
    int j;
    int UpperLower;
    char letter;
    FILE * fp;

    fp = fopen("dataset2.txt", "w");

    srand(time(NULL));

    for(i = 0; i < SIZE; i++){

        for(j = 0; j < LEN; j++){

            UpperLower = rand() % 2;

            if(UpperLower == 0){
                letter = (char)(rand() % 26 + 65);
                fprintf(fp, "%c", letter);
            }

            else if(UpperLower == 1){
                letter = (char)(rand() % 26 + 97);
                fprintf(fp, "%c", letter);
            }

        }

        fprintf(fp, "\n");

    }

    fclose(fp);

    return 0;
}