# 排序/Sort



## 时间复杂度$O(n^2)$的排序算法



### 冒泡排序

冒泡排序有三种写法：

1. 基础的冒泡排序：一边比较一边向后两两交换

代码实现（升序）：

```c
void BubbleSort(int *arr, int size) {
    int tmp;
    
    for(int i = 0; i < size-1; i++) {
        for(int j = 0; j < size-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}
```

2. 优化，使用一个变量记录某轮次是否存在交换

代码实现：

```c
void BubbleSort(int *arr, int size) {
    bool swap;
    
    for(int i = 0; i < size-1; i++) {
        swap = false;
        for(int j = 0; j < size-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                
                swap = true;
            }
        }
        if(!swap) {
            break;
        }
    }
}
```

当某一轮已不存在变量交换位置，意味着排序已经结束，之后的步骤不需要再执行。

3. 进一步优化，除了记录是否交换外，再使用一个变量记录上次最后一次发生交换的位置

代码实现：

```c
void BubbleSort(int *arr, int size) {
    bool swap;
    int indexOfLastUnsortedEle, tmp, swapIndex;
    
    swap = true;
    swapIndex = -1;
    indexOfLastUnsortedEle = size - 1;
    while(swap) {
        swap = false;
        for(int i = 0; i < indexOfLastUnsortedEle; i++) {
            if(arr[i] > arr[i+1]) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                
                swap = true;
                swapIndex = i;
            }
        }
        indexOfLastUnsortedEle = swapIndex;
    }
}
```

冒泡排序中没有交换就意味着有序，最后一次交换后的数组必然已经是有序的，没必要再去比较访问。

#### 交换技巧

一般的操作

```c
int tmp = arr[i];
arr[i] = arr[j];
arr[j] = tmp;
```

利用数学特性

```c
// 先加后减
arr[j] = arr[i] + arr[j];
arr[i] = arr[j] - arr[i];
arr[j] = arr[j] - arr[i];

// 先减后加
arr[j] = arr[i] - arr[j];
arr[i] = arr[i] - arr[j];
arr[j] = arr[i] + arr[j];
```

由于涉及算数运算，可能导致数组越界

对于整数还可以采用位运算

```c
arr[i] = arr[i] ^ arr[j];
arr[j] = arr[i] ^ arr[j];
arr[i] = arr[i] ^ arr[j];
```

#### 复杂度分析

空间复杂度为$O(1)$，时间复杂度为$O(n^2)$

在有序（最好情况）的条件下，后两种优化的时间复杂度为$O(n)$，但平均复杂度为$O(n^2)$，并没有提升冒泡排序的性能。



