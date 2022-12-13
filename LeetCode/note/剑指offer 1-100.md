# 剑指offer 1-100



## 40.最小的k个数(简单)

https://leetcode.cn/problems/zui-xiao-de-kge-shu-lcof/description/

```c
void swap(int *arr, int i, int j) {
    int tmp;
    
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void minHeapify(int *arr, int size, int index) {
    int min_index, left, right;
    
    min_index = index;
    left = (index << 1) + 1;
    right = left + 1;
    
	min_index = left < size && arr[left] < arr[min_index] ? left : min_index;
    min_index = right < size && arr[right] < arr[min_index] ? right : min_index;
    
    if(min_index != index) {
        swap(arr, index, min_index);
        minHeapify(arr, size, min_index);
        // 递归，保证子树还是最大堆
    }  
}

void buildMinHeap(int *arr, int size) {
    for(int i = (size >> 1) - 1; i >= 0; i--) {
        minHeapify(arr, size, i);
    }
}

int* getLeastNumbers(int* arr, int arrSize, int k, int* returnSize){
    int *leastNums;

    leastNums = (int*)malloc(sizeof(int)*k);

    buildMinHeap(arr, arrSize);
    
    for(int i = 0; i < k; i++) {
        leastNums[i] = arr[0];
        swap(arr, 0, arrSize-1-i);
        minHeapify(arr, arrSize-1-i, 0);
    }

    *returnSize = k;

    return leastNums;
}
```

