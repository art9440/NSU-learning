#include <stdio.h>
#include <malloc.h>


#define START 0


void swap(int *a, int *b){ //swaps two array elements
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


void quickSort(int* arr, int left, int right) //quick Sort of array
{
    if (left < right) {
        int mid = arr[(left + right) / 2];
        int i = left, j = right;

        while (i <= j)
        {

            while (arr[i] < mid)
                i++;

            while (arr[j] > mid)
                j--;

            if (i <= j)
                swap(&arr[i++], &arr[j--]);

        }

        quickSort(arr, left, j);
        quickSort(arr, i, right);
    }
}


int main(){
    int N;
    scanf("%d", &N);
    int left = START, right = N - 1;
    int *arr = (int*)malloc(N * sizeof(int));

    for (int i = START; i < N; i++)
        scanf("%d", &arr[i]);

    quickSort(arr, left, right);

    for(int i = START; i < N; i++)
        printf("%d ", arr[i]);

    free(arr);

    return 0;
}