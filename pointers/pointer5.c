#include <stdio.h>
//Cannot return two values from a function
void minMax(int arr[], int n, int *min, int *max) {
    *min = *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
    
}

int main(void) {
    int data[] = {42, 7, 19, 88, 3, 56};
    int lo, hi;

    minMax(data, 6, &lo, &hi);
    printf("Min = %d, Max = %d\n", lo, hi);   // Min = 3, Max = 88
   
    return 0;
}