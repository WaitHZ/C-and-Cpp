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

<p style='color: red'>需要注意的是，必须满足i≠j，否则会使得该存储空间存放的整数为0，造成数据丢失。</p>

#### 复杂度分析

空间复杂度为$O(1)$，时间复杂度为$O(n^2)$

在有序（最好情况）的条件下，后两种优化的时间复杂度为$O(n)$，但平均复杂度为$O(n^2)$，并没有提升冒泡排序的性能。



### 选择排序

思想：双重循环遍历数组，每经过一轮比较，找到最小元素的下标，将其交换至首位。

```c
void SelectionSort(int *arr, int size) {
    int min_index;
    
    for(int i = 0; i < size-1; i++) {
        min_index = i;
        for(int j = i+1; j < size; j++) {
            if(arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if(min_index != i) {
        	swap(arr, i, min_index);
        }
    }
}

void swap(int *arr, int i, int j) {
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[i] ^ arr[j];
    arr[i] = arr[i] ^ arr[j];
}
```

#### 与冒泡排序的比较

##### 相同点

时间复杂度均为$O(n^2)$，空间复杂度均为$O(1)$.

##### 不同点

- 选择排序通过存储索引减少了交换发生的次数
- 选择排序算法是不稳定的，而冒泡排序是稳定的

#### 排序算法的稳定性

假定在待排序序列中，存在多个具有相同关键字的记录，若经过排序，这些记录的相对排序不变，即在原序列中$a[i] = a[j]$且$i<j$，排序后$a[i]$仍在$a[j]$之前，则称排序算法是稳定的，否则就是不稳定的

不难验证选择排序算法是不稳定的，而冒泡排序是稳定的

排序的稳定与否仅在一种情况下存在意义，即排序内容是一个对象的多个属性，且其原本的属性存在意义时，如果希望二次排序保证原有排序中的意义，就需要使用稳定的排序算法。如，一个商品先按照价格排序，再按照销量排序，如果希望销量相同时，价格的排序规则和价格排序时一致，就需要使用稳定的排序算法。

稳定与否与算法的具体实现有关，如冒泡排序若将$<$变为$\le$，算法就变为不稳定的排序。

选择排序也可以实现稳定排序：

```c
int* stableSelectionSort(int *arr, int size) {
    int *new_arr, min_index, index;
    const int max = 10000;  // 定义一个数组元素取不到的量
    
    index = 0;
    
    new_arr = (int*)malloc(sizeof(int)*size);
    
    for(int i = 0; i < size; i++) {
        min_index = findIndexOfMinEle(arr, size);
        new_arr[count++] = arr[min_index];
        arr[min_index] = max;
    }
    
    return new_arr;
}

int findIndexOfMinEle(int *arr, int size) {
    int min_index;
    
    min_index = 0;
    
    for(int i = 1; i < size; i++) {
        if(arr[min_index] > arr[i]) {
            min_index = i;
        }
    }
    
    return min_index;
}
```

利用选择排序的思想在$O(n^2)$的时间复杂度实现了稳定的排序算法，注意，若将$>$改为$\ge$，则算法仍旧不稳定。

#### 优化——二元选择排序

过程中同时找到最小值和最大值，并做交换

```c
void SelectionSort(int *arr, int size) {
    int min_index, max_index, last_index;
    
    for(int i = 0; i < size/2; i++) {
        min_index = i;
        max_index = i;
        for(int j = i+1; j < size - i; j++) {
            if(arr[j] < arr[min_index]) {
                min_index = j;
            }
            if(arr[j] > arr[max_index]) {
                max_index = j;
            }
        }
        
        // 剪枝优化，在数组中存在大量相同元素时提升效率
        if(min_index == max_index) {
            break;
        }
        
        swap(arr, i, min_index);
        
        // 避免最大值多因就是i
        if(max_index == i) {
            max_index = min_index;
        }
        
        last_index = size - 1 - i;
        swap(arr, last_index, max_index);
    }
}

void swap(int *arr, int i, int j) {
    int tmp;
    
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
```

优化（含**剪枝优化**）在复杂度上并没有提升，且仍为不稳定的排序算法。但在实际使用中，会因为较少的比较次数而得到一定的优化。



### 插入排序

插入排序有两种写法：

- 交换法：在新数字插入的过程中，不断与之前的元素交换，直到找到自己合适的位置
- 移动法：新数字插入过程中，与前面的数字不断比较，前面的数字不断向后挪出位置，当新数字找到自己的位置后，插入一次即可

交换法代码：

```c
void insertSort(int *arr, int size) {
	// 一个一定是有序的
    for(int i = 1; i < size; i++) {
        int j = i;
        // 避免数组越界
        while(j >= 1 && arr[j] > arr[j-1]) {
            swap(arr, j, j-1);
            j -= 1;
        }
    }
}

void swap(int *arr, int i, int j) {
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[j] ^ arr[i];
    arr[i] = arr[i] ^ arr[j];
}
```

移动法代码：

```c
void insertSort(int *arr, int size) {
    for(int i = 1; i < size; i++) {
        int j  = i-1;
        int current_num = arr[i];
        while(j >= 0 && arr[j] > current_num) {
            arr[j+1] = arr[j];
            j -= 1;
        }
        
        arr[j+1] = current_num;
    }
}
```

将原先的三次赋值优化为一次

#### 分析

插入排序是稳定的排序算法

时间复杂度为$O(n^2)$，空间复杂度为$O(1)$

**在数组几乎有序的情形下，插入排序的时间复杂度接近线性**



## 时间复杂度$O(nlogn)$的排序算法



### 希尔排序





