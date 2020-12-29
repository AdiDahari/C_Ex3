#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "isort.h"
#define SIZE 50
void printArray(int *arr, int len){
    for(int i = 0; i < len; i++){
        printf("%d", *(arr+i));
        if(i < len-1) printf(",");
    }
    printf("\n");
}
void shift_element(int* arr, int i){
    for(; i > 0; i--){
        *(arr+i) = *(arr+i-1);
    }
}
void insertion_sort(int* arr , int len){
    for(int i = 0; i < len; i++){
        printf("Iteration = %d\n", i+1);
        if(*(arr+i+1) < *(arr+i) && *(arr+i+1) != 0){
            printf("%d, %d\n", *(arr+i), *(arr+i+1));
            int tmp = *(arr+i+1);
            printf("tmp = %d\n", tmp);
            int count = 0;
            while(tmp < *(arr+i-count) && count <= i){
                count++;
            }
            printf("element to shift from = %d, count = %d\n", *(arr+i-count+1), count);
            shift_element(arr+i-count+1, count);
            *(arr+i-count+1) = tmp;
            printf("array is: ");
            printArray(arr, len);
        }
    }  
}

int main(){
    int *arr = NULL;
    //Memory allocation
    arr = (int*)calloc(SIZE+1, sizeof(int));
    if(arr == NULL){
        printf("Failed to allocate memory space. Exiting...");
        return -1;
    }
    int count = 0;
    printf("Please enter 50 natural numbers to the array, which will be sorted in an ascending order,\n\
To stop the insertion and sort the current array enter '-1'\n\n");
    for(int i = 0; i < SIZE; i++){
        printf("Number #%d: ", i+1);
        while(scanf(" %d", (arr+i)) == false || *(arr+i) < -1){
            printf("Invalid input! please try again.\n");
        };
        if(*(arr+i) == -1) break;
        count++;
    }
    printf("The array as inserted is:\n");
    printArray(arr, count);
    printf("The sorted array is:\n");
    insertion_sort(arr,count);
    printArray(arr, count);
    free(arr);
    return 0;
}