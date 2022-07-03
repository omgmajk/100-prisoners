/* compile with cc -g -Wall 100prisoners.c -o 100prisoners */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define ARR_SIZE 100

static int prisoners[ARR_SIZE], boxes[ARR_SIZE];
static bool they_live = true;

void fill_arrays() {
    for (int i = 0; i < ARR_SIZE; i++) {
        prisoners[i] = i;
        boxes[i] = i;
    }
}

void swap(int *pa, int *pb) {
    int t = *pa;
    *pa = *pb;
    *pb = t;
}

void shuffle(int *arr, size_t n) {
    srand(time(NULL)); // Seed random, only works once per second.
    for(size_t i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

void print_array(int *arr, size_t n) {
        for(int i = 0; i < ARR_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}



int main(void) {


    fill_arrays();

    printf("Original array of prisoners:\n");
    print_array(prisoners, ARR_SIZE);
    printf("Original array of boxes:\n");
    print_array(boxes, ARR_SIZE);
    shuffle(boxes, ARR_SIZE);
    printf("Shuffled array of boxes:\n");
    print_array(boxes, ARR_SIZE);

    // Prisoners go to the box with their number on them, then goes to the box with the number in the first box.
    for(int i = 0; i < ARR_SIZE && they_live; i++) {
        int current_prisoner = prisoners[i];
        printf("Prisoner %d is ready to start their search.\n", current_prisoner);
        int count = 1;
        int current_box = current_prisoner;
        for(int j = 0; j < ARR_SIZE && they_live; j++) {
            if(count > ARR_SIZE / 2) {
                printf("Oh no! Prisoner %d took too many tries (%d).\n", current_prisoner, count);
                they_live = false;
                break;
            }
            printf("Prisoner %d searches box %d and finds %d\n", current_prisoner, current_box, boxes[current_box]);
            if(current_prisoner == boxes[current_box]) {
                printf("It took %d tries for prisoner %d to find their number.\n", count, current_prisoner);
                break;
            }
            current_box = boxes[current_box];
            count++;
        }
    }

    printf("All the prisoners %s!\n", they_live ? "survived" : "got execuded");

    return EXIT_SUCCESS;
}
