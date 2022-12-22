#ifndef __SORT_H__
#define __SORT_H__

#include <stdlib.h>

typedef int ElementType;
typedef int Position;

int compare(ElementType a, ElementType b) {
    int retVal;
    
    if(a < b) {
        retVal = -1;
    }
    else if(a == b) {
        retVal = 0;
    }
    else {
        retVal = 1;
    }

    return retVal;
}


// MergeSort Recursion
void merge(ElementType *arr, int start, int end, int (*compare)(ElementType a, ElementType b), ElementType *tmp) {
    int end1, start2, ptr1, ptr2, ptr;
    
    end1 = (end-start) / 2 + start;
    start2 = end1 + 1;
    
    ptr = ptr1 = start; ptr2 = start2;
    while(ptr1 <= end1 || ptr2 <= end) {
        if(ptr1 <= end1 && ptr2 <= end) {
            if(compare(arr[ptr1], arr[ptr2]) <= 0) {
                tmp[ptr++] = arr[ptr1++];
            }
            else {
                tmp[ptr++] = arr[ptr2++];
            }
        }
        else if(ptr1 <= end1) {
            tmp[ptr++] = arr[ptr1++];
        }
        else {
            tmp[ptr++] = arr[ptr2++];
        }
    }
    
    for(ptr = start; ptr <= end; ptr++) {
        arr[ptr] = tmp[ptr];
    }
}

void MergeSort(ElementType* arr, int (*compare)(ElementType a, ElementType b), Position start, Position end, ElementType *tmp) {
    int mid;

    if(end > start) {
        mid = (end-start) / 2 + start;
        
        MergeSort(arr, compare, start, mid, tmp);
        MergeSort(arr, compare, mid+1, end, tmp);
        
        merge(arr, start, end, compare, tmp);
    }
}

void mergeSort_recursion(ElementType *arr, int arrSize, int (*compare)(ElementType a, ElementType b)) {
    ElementType *tmp;

    if(arrSize == 1) {
        return ;
    }

    tmp = (ElementType*)malloc(sizeof(ElementType)*arrSize);
    MergeSort(arr, compare, 0, arrSize-1, tmp);

    free(tmp);
}
////////////////////////////////////////////////////////////////////////////////////////////////


#endif