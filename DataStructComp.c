#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include "DataStructCompHeader.h"

#define HASHSIZE 53810

struct treenode{
    int key;
    struct treenode *left;
    struct treenode *right;
};

struct listnode{
    int key;
    struct listnode *next;
};

int main(int argc, char **argv){

    int i;
    int j;
    int nsize = 1;
    int msize = 1;
    int *data;
    int *sdata;

    for(i = 1; i < argc; i++){

        if(strcmp(&argv[i][0], "-d") == 0){
            i++;
            for(j = 0; j < atoi(&argv[i][2]); j++){
                nsize = nsize * 10;
            }
            data = GenerateData(nsize);
        }
        
        else if(strcmp(&argv[i][0], "-q") == 0){
            i++;
            for(j = 0; j < atoi(&argv[i][2]); j++){
                msize = msize * 10;
            }
            sdata = GenerateSearchData(msize, nsize);
        }

        else if(strcmp(&argv[i][0], "-bst") == 0){
            BST(data, sdata, nsize, msize);
        }

        else if(strcmp(&argv[i][0], "-bs") == 0){
            BS(data, sdata, nsize, msize);
        }

        else if(strcmp(&argv[i][0], "-arr") == 0){
            Arr(data, sdata, nsize, msize);
        }

        else if(strcmp(&argv[i][0], "-ll") == 0){
            LL(data, sdata, nsize, msize);
        }

        else if(strcmp(&argv[i][0], "-hash") == 0){
            Hash(data, sdata, nsize, msize);
        }

    }

    free(data);
    free(sdata);

    return 0;
}

/********** Generate data and sdata **********/

void swap(int *a, int *b){

    int temp;

    temp = *a;
    *a = *b;
    *b = temp;

}

int *GenerateData(int nsize){

    int i;
    int index1;
    int index2;
    int *data = malloc(sizeof(int) * nsize);

    for(i = 0; i < nsize; i++){
        data[i] = i;
    }

    srand(time(NULL));
    for(i = 0; i < nsize; i++){
        index1 = rand() % nsize;
        index2 = rand() % nsize;
        swap(&data[index1], &data[index2]);
    }

    return data;

}

int *GenerateSearchData(int msize, int nsize){

    int i;
    int *sdata = malloc(sizeof(int) * msize);

    srand(time(NULL));
    for(i = 0; i < msize; i++){
        sdata[i] = rand() % nsize;
    }

    return sdata;

}

/********** end of Generate data and sdata **********/

/********** BST **********/

struct treenode *InsertBST(struct treenode *root, int key){

    if(root == NULL){
        struct treenode *newnode = malloc(sizeof(struct treenode));
        newnode -> key = key;
        newnode -> left = NULL;
        newnode -> right = NULL;
        return newnode;
    }

    else if(key < root -> key){
        root -> left = InsertBST(root -> left, key);
    }

    else if(key > root -> key){
        root -> right = InsertBST(root -> right, key);
    }

    else{
        return root;
    }

    return root;

}

struct treenode *SearchBST(struct treenode *root, int key){

    if(root == NULL){
        return NULL;
    }

    else if(key < root -> key){
        return SearchBST(root -> left, key);
    }

    else if(key > root -> key){
        return SearchBST(root -> right, key);
    }

    else{
        return root;
    }

}

void FreeBST(struct treenode *root){

    if(root == NULL)return;
    FreeBST(root -> left);
    FreeBST(root -> right);
    free(root);

}

void BST(int *data, int *sdata, int nsize, int msize){

    struct  timeval startBuild;
    struct  timeval endBuild;
    struct  timeval startSearch;
    struct  timeval endSearch;
    unsigned  long diffBuild;
    unsigned  long diffSearch;
    int i;
    struct treenode *root = NULL;
    struct treenode *node = NULL;

    //BST title
    printf("BST:\n");

    //BST building time
    gettimeofday(&startBuild,NULL);
    for(i = 0; i < nsize; i++){
        root = InsertBST(root, data[i]);
    }
    gettimeofday(&endBuild,NULL);
    diffBuild = 1000000 * (endBuild.tv_sec-startBuild.tv_sec) + endBuild.tv_usec-startBuild.tv_usec;
    printf("building time: %ld µs\n",diffBuild);

    //BST searching time
    gettimeofday(&startSearch,NULL);
    for(i = 0; i < msize; i++){
        node = SearchBST(root, sdata[i]);
    }
    gettimeofday(&endSearch,NULL);
    diffSearch = 1000000 * (endSearch.tv_sec-startSearch.tv_sec) + endSearch.tv_usec-startSearch.tv_usec;
    printf("searching time: %ld µs\n",diffSearch);

    printf("\n");

    FreeBST(root);

}

/********** end of BST **********/

/********** Binary Search **********/

int comp(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

void SearchBS(int *arr, int len, int key){

    int low = 0;
    int high = len - 1;
    int mid;

    while(low <= high){

        mid = (low + high) / 2;

        if(key == arr[mid]){
            return;
        }
        else if(key < arr[mid]){
            high = mid - 1;
        }
        else if(key > arr[mid]){
            low = mid + 1;
        }
    }

}

void BS(int *data, int *sdata, int nsize, int msize){

    struct  timeval startBuild;
    struct  timeval endBuild;
    struct  timeval startSearch;
    struct  timeval endSearch;
    unsigned  long diffBuild;
    unsigned  long diffSearch;
    int i;
    int arr[nsize];

    //BS title
    printf("BS:\n");

    //BS building time
    gettimeofday(&startBuild,NULL);
    for(i = 0; i < nsize; i++){
        arr[i] = data[i];
    }
    qsort(arr, nsize, sizeof(int), comp);
    gettimeofday(&endBuild,NULL);
    diffBuild = 1000000 * (endBuild.tv_sec-startBuild.tv_sec)+ endBuild.tv_usec-startBuild.tv_usec;
    printf("building time: %ld µs\n",diffBuild);

    //BS searching time
    gettimeofday(&startSearch,NULL);
    for(i = 0; i < msize; i++){
        SearchBS(arr, nsize, sdata[i]);
    }
    gettimeofday(&endSearch,NULL);
    diffSearch = 1000000 * (endSearch.tv_sec-startSearch.tv_sec)+ endSearch.tv_usec-startSearch.tv_usec;
    printf("searching time: %ld µs\n",diffSearch);

    printf("\n");

}

/********** end of Binary Search **********/

/********** Array **********/

void SearchArr(int *arr, int len, int key){
    
    int i;

    for(i = 0; i < len; i++){
        if(arr[i] == key){
            return;
        }
    }

}

void Arr(int *data, int *sdata, int nsize, int msize){

    struct  timeval startBuild;
    struct  timeval endBuild;
    struct  timeval startSearch;
    struct  timeval endSearch;
    unsigned  long diffBuild;
    unsigned  long diffSearch;
    int i;
    int arr[nsize];

    //Arr title
    printf("Arr:\n");

    //Arr building time
    gettimeofday(&startBuild,NULL);
    for(i = 0; i < nsize; i++){
        arr[i] = data[i];
    }
    gettimeofday(&endBuild,NULL);
    diffBuild = 1000000 * (endBuild.tv_sec-startBuild.tv_sec)+ endBuild.tv_usec-startBuild.tv_usec;
    printf("building time: %ld µs\n",diffBuild);

    //Arr searching time
    gettimeofday(&startSearch,NULL);
    for(i = 0; i < msize; i++){
        SearchArr(arr, nsize, sdata[i]);
    }
    gettimeofday(&endSearch,NULL);
    diffSearch = 1000000 * (endSearch.tv_sec-startSearch.tv_sec)+ endSearch.tv_usec-startSearch.tv_usec;
    printf("searching time: %ld µs\n",diffSearch);

    printf("\n");

}

/********** end of Array **********/

/********** Linked List **********/

struct listnode *InsertLL(struct listnode *head, int key){

    struct listnode *cur;
    struct listnode *newnode = malloc(sizeof(struct listnode));
    newnode -> key = key;
    newnode -> next = NULL;

    if(head == NULL){
        return newnode;
    }

    cur = head;

    while(cur -> next){
        cur = cur -> next;
    }

    cur -> next = newnode;
    return head;

}

struct listnode *SearchLL(struct listnode *head, int key){

    struct listnode *cur;

    cur = head;

    while(cur){
        if(cur -> key == key){
            return cur;
        }
        else{
            cur = cur -> next;
        }
    }

    return NULL;
}

void FreeList(struct listnode *head){

    struct listnode *pre;

    while(head){
        pre = head;
        head = head -> next;
        free(pre);
    }
    
}

void LL(int *data, int *sdata, int nsize, int msize){

    struct  timeval startBuild;
    struct  timeval endBuild;
    struct  timeval startSearch;
    struct  timeval endSearch;
    unsigned  long diffBuild;
    unsigned  long diffSearch;
    int i;
    struct listnode *head = NULL;
    struct listnode *node = NULL;

    //LL title
    printf("LL:\n");

    //LL building time
    gettimeofday(&startBuild,NULL);
    for(i = 0; i < nsize; i++){
        head = InsertLL(head, data[i]);
    }
    gettimeofday(&endBuild,NULL);
    diffBuild = 1000000 * (endBuild.tv_sec-startBuild.tv_sec)+ endBuild.tv_usec-startBuild.tv_usec;
    printf("building time: %ld µs\n",diffBuild);

    //LL searching time
    gettimeofday(&startSearch,NULL);
    for(i = 0; i < msize; i++){
        node = SearchLL(head, sdata[i]);
    }
    gettimeofday(&endSearch,NULL);
    diffSearch = 1000000 * (endSearch.tv_sec-startSearch.tv_sec)+ endSearch.tv_usec-startSearch.tv_usec;
    printf("searching time: %ld µs\n",diffSearch);

    printf("\n");

    FreeList(head);

}

/********** end of Linked List **********/

/********** Hash **********/

int HashFunction(int key){

    int index;

    index = key % HASHSIZE;

    return index;
}

struct listnode *InsertHash(struct listnode *listHead, int key){

    struct listnode *cur;
    struct listnode *newnode = malloc(sizeof(struct listnode));

    newnode -> key = key;
    newnode -> next = NULL;

    if(listHead == NULL){
        return newnode;
    }

    cur = listHead;

    while(cur -> next){
        cur = cur -> next;
    }

    cur -> next = newnode;

    return listHead;

}

void SearchHash(struct listnode *listHead, int key){

    struct listnode *cur;

    cur = listHead;

    while(cur){
        if(cur -> key == key){
            return;
        }
        cur = cur -> next;
    }

}

void Hash(int *data, int *sdata, int nsize, int msize){

    struct  timeval startBuild;
    struct  timeval endBuild;
    struct  timeval startSearch;
    struct  timeval endSearch;
    unsigned  long diffBuild;
    unsigned  long diffSearch;
    int i;
    int index;
    struct listnode *hashTable[HASHSIZE] = {NULL};


    //Hash title
    printf("Hash:\n");

    //Hash building time
    gettimeofday(&startBuild,NULL);
    for(i = 0; i < nsize; i++){
        index = HashFunction(data[i]);
        hashTable[index] = InsertHash(hashTable[index], data[i]);
    }
    gettimeofday(&endBuild,NULL);
    diffBuild = 1000000 * (endBuild.tv_sec-startBuild.tv_sec)+ endBuild.tv_usec-startBuild.tv_usec;
    printf("building time: %ld µs\n",diffBuild);

    //Hash searching time
    gettimeofday(&startSearch,NULL);
    for(i = 0; i < msize; i++){
        index = HashFunction(sdata[i]);
        SearchHash(hashTable[index], sdata[i]);
    }
    gettimeofday(&endSearch,NULL);
    diffSearch = 1000000 * (endSearch.tv_sec-startSearch.tv_sec)+ endSearch.tv_usec-startSearch.tv_usec;
    printf("searching time: %ld µs\n",diffSearch);

    printf("\n");

}

/********** end of Hash **********/