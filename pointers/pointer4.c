#include <stdio.h>
// void doubleAll(int arr[],   int n);
// void doubleAll(int *arr,    int n);
// void doubleAll(int arr[10], int n);

//when array is passed to a function

void doubleAll(int arr[], int n) {
    printf("Inside : arr       = %p\n",arr);
    printf("Inside : sizeof    = %d bytes\n", sizeof(arr));   // size of a pointer!

    for (int i = 0; i < n; i++) {
        arr[i] = arr[i] * 2;     // writes into main's array
        //*(arr + i) = *(arr + i) *2;
    }
}

int main(void) {
    int nums[5] = {1, 2, 3, 4, 5};
    int n = sizeof(nums) / sizeof(nums[0]);   // 20 / 4 = 5 elements

    printf("In main: &nums[0]  = %p\n", &nums[0]);
    printf("In main: sizeof    = %d bytes\n", sizeof(nums));   // whole array

    doubleAll(nums, n);

    printf("After call: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    return 0;
}