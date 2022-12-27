#ifndef __SORT_H__
#define __SORT_H__

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

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


// quick sort
ElementType partition(ElementType *arr, Position start, Position end, int (*compare)(ElementType a, ElementType b)) {
    int pivot;
    Position left, right, random_index;
    ElementType tmp;

    random_index = start + rand()%(end-start+1);
    tmp = arr[start];
    arr[start] = arr[random_index];
    arr[random_index] = tmp;


    pivot = arr[start];
    left = start + 1;
    right = end;

    while(left < right) {
        while(left < right && compare(arr[left], pivot) <= 0) {
            left += 1;
        }

        while(right > left && compare(arr[right], pivot) >= 0) {
            right -= 1;
        }

        if(left != right) {
            tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;

            right -= 1;
            left += 1;
        }
    }

    if(left == right && compare(arr[right], pivot) > 0) {
        right -= 1;
    }

    tmp = arr[start];
    arr[start] = arr[right];
    arr[right] = tmp;

    return right;
}

void QuickSort(ElementType *arr, Position start, Position end, int (*compare)(ElementType a, ElementType b)) {
    int mid;

    if(start < end) {
        mid = partition(arr, start, end, compare);

        QuickSort(arr, start, mid-1, compare);
        QuickSort(arr, mid+1, end, compare);
    }
}

void quickSort(ElementType *arr, int arrSize, int (*compare)(ElementType a, ElementType b)) { 
    bool isSorted, isReversed;
    ElementType tmp;
    
    srand(time(NULL));
    
    if(arrSize >= 10000) {
        
        isSorted = isReversed = true;

        for(int i = 1; i < arrSize; i++) {
            if(arr[i] < arr[i-1]) {
                isSorted = false;
            }
            if(arr[i] > arr[i-1]) {
                isReversed = false;
            }

            if(!isReversed && !isSorted) {
                break;
            }
        }

        if(isReversed) {
            for(int i = 0; i < arrSize/2; i++) {
                tmp = arr[i];
                arr[i] = arr[arrSize-1-i];
                arr[arrSize-1-i] = tmp;
            }
        }
        else if(!isReversed && !isSorted) {
            QuickSort(arr, 0, arrSize-1, compare);
        }
    }
    else {
        QuickSort(arr, 0, arrSize-1, compare);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////


// counting sort
int getIntVal(ElementType a) {
    return a;
}

void countingSort(ElementType *arr, int arrSize, int(*getIntVal)(ElementType a)) {
    int max, min, *count, *res;

    max = min = getIntVal(arr[0]);
    for(int i = 0; i < arrSize; i++) {
        if(getIntVal(arr[i]) > max) {
            max = getIntVal(arr[i]);
        }
        if(getIntVal(arr[i]) < min) {
            min = getIntVal(arr[i]);
        }
    }

    count = (int*)malloc(sizeof(int)*(max-min+1));
    memset(count, 0, sizeof(int)*(max-min+1));

    for(int i = 0; i < arrSize; i++) {
        count[getIntVal(arr[i])-min] += 1;
    }

    count[0] -= 1;
    for(int i = 1; i < max-min+1; i++) {
        count[i] += count[i-1];
    }

    res = (int*)malloc(sizeof(ElementType)*arrSize);
    for(int i = arrSize-1; i >= 0; i--) {
        res[count[getIntVal(arr[i])-min]] = arr[i];
        count[getIntVal(arr[i])-min] -= 1;
    }

    for(int i = 0; i < arrSize; i++) {
        arr[i] = res[i];
    }

    free(res);
    free(count);
}
////////////////////////////////////////////////////////////////////////////////

// radixSort
int absVal(int x) {
    return x < 0 ? -x : x;
}

void radixSort(ElementType *arr, int arrSize, int(*getIntVal)(ElementType a)) {
    int max = 0, maxDigitLength, count[19], dev, radix;
    ElementType *res;
    
    for(int i = 0; i < arrSize; i++) {
        if(absVal(getIntVal(arr[i])) > max) {
            max = absVal(getIntVal(arr[i]));
        }
    }

    maxDigitLength = 0;
    while(max) {
        maxDigitLength += 1;
        max /= 10;
    }

    res = (ElementType*)malloc(sizeof(ElementType)*arrSize);
    dev = 1;
    for(int i = 0; i < maxDigitLength; i++) {
        memset(count, 0, sizeof(int)*19);
        for(int j = 0; j < arrSize; j++) {
            radix = getIntVal(arr[j]) / dev % 10;
            count[radix+9] += 1;
        }

        count[0] -= 1;
        for(int j = 1; j < 19; j++) {
            count[j] += count[j-1];
        }

        for(int j = arrSize-1; j >= 0; j--) {
            radix = getIntVal(arr[j]) / dev % 10;
            res[count[getIntVal(arr[j])/dev%10+9]] = arr[j];
            count[getIntVal(arr[j])/dev%10+9] -= 1;
        }

        memcpy(arr, res, sizeof(ElementType)*arrSize);
        dev *= 10;
    }

    free(res);
}
///////////////////////////////////////////////////////////////////////////////


#endif