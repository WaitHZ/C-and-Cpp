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

希尔排序是对插入排序的一种优化，基本思想为：

- 将待排序数组按照一定的间隔分为多个子数组，每组分别进行插入排序。这里按照间隔分组指的不是取连续的一段数组，而是每跳跃一定间隔取一个值组成一组
- 逐渐缩小间隔进行下一轮排序
- 最后一轮时，取间隔为1，也就相当于直接使用插入排序。但这时经过前面的**宏观调控**，数组已经基本有序了，所以此时的插入排序只需进行少量交换便可完成

*在插入排序时提到，在接近有序的数组中，插入排序的时间复杂度接近线性

**注意到在更小间隔排序时，并不会破坏较大间隔排序的有序性**

每一遍排序的间隔在希尔排序中被称之为**增量**，所有的增量组成的序列称之为**增量序列**。增量依次递减，最后一个增量必须为1，所以希尔排序又被称之为**缩小增量排序**。因此，排序分为以下两个步骤:

- 定义增量序列$D_m > D_{m-1} >...>D_2>D_1=1$
- 对每个$D_k$进行间隔插入排序

希尔排序的性能由下面这条性质保证：

- $D_{k+1}$间隔有序再经过$D_k$间隔排列后仍满足$D_{k+1}$间隔有序

**增量序列的选择会极大程度的影响希尔排序的效率**，常见的增量序列如下：

#### 希尔增量

希尔增量序列：$D_m=\frac{N}{2},\,D_{k+1}=\frac{D_k}{2}$

```c
void shellSort(int *arr, int size) {
    int gap;
    
    gap = size / 2;
    
    while(gap > 0) {
        for(int i = 0; i < gap; i++) {
            for(int j = i+gap; j < size; j+=gap) {
                int currentNum, index;
                
                currentNum = arr[j];
                index = j - gap;
                while(index >= i && arr[index] > currentNum) {
                    arr[index+gap] = arr[index];
                    index -= gap;
                }
                
                arr[index+gap] = currentNum;
            }
        }
        gap /= 2;
    }
}
```

从访存的角度考虑，跳跃式访存的速度会慢于访问连续的内存，因此代码可进一步优化：

```c
void shellSort(int *arr, int size) {
    int gap;
    
    gap = size / 2;
    
    while(gap > 0) {
        for(int i = gap; i < size; i++) {
            int currentNum, index;
            
            currentNum = arr[i];
            index = i - gap;
            while(index >= 0 && arr[index] > currentNUm) {
                arr[index+gap] = arr[index];
                index -= gap;
            }
            arr[index+gap] = currentNum;
        }
        gap /= 2;
    }
}
```

研究者发现，**增量元素不互质，则小增量可能根本不起作用**。希尔增量序列一旦出现偶数就会导致不互质，从而增加许多无用的操作，效率较低。

#### 希伯德(Hibbard)增量序列

- $D_k=2^k-1$，即$1, 3, 7, 15$...数学界猜想其最坏的时间复杂度为$O(n^{\frac{3}{2}})$，平均时间复杂度为$O(n^{\frac{5}{4}})$

#### Knuth增量序列

- $D_1=1,\,D_{k+1}=3D_k+1$，即$1,4,13,40$...数学界猜想其平均时间复杂度为$O(n^{\frac{3}{2}})$

#### Sedgewick增量序列

- $1,5,19,41,109,$... 有的元素依据$9\times4^k−9\times2^k+1$计算得到，有的元素依据$4^k−3\times2^k+1$计算得到。数学界猜想其最坏的时间复杂度为$O(n^{\frac{4}{3}})$，平均时间复杂度为$O(n^{\frac{7}{6}})$

*以上时间复杂度都未得到证明，只是数学界的猜想

以Knuth增量序列为例，编写下方代码：

```c
void shellSort(int *arr, int size) {
    int gap;
    
    gap = 1;
    while(gap < size/3) {
        gap = gap * 3 + 1;
    }
    
    while(gap > 0) {
        for(int i = gap; i < size; i++) {
            int currentNum, index;
            
            currentNum = arr[i];
            index = i - gap;
            while(index >= 0 && arr[index] > currentNum) {
                arr[index+gap] = arr[index];
                index -= gap;
            }
            arr[index+gap] = currentNum;
        }
        gap = (gap - 1) / 3;
    }
}
// 时间复杂度小于平方，但无法得到具体数值
```

#### 分析

希尔排序不是稳定的排序算法

时间复杂度介于$O(n)$与$O(n^2)$之间，普遍认为最好的时间复杂度是$O(n^{1.3})$

空间复杂度为$O(1)$



希尔排序之所以能够打破空间复杂度$O(1)$的限制下，时间复杂度无法超过$O(n^2)$的魔咒，大致原因如下：

**排序算法本质上就是一个消除逆序对的过程。**对于随机数组，逆序对的数量是$O(n^2)$级的，如果采用交换相邻元素的办法来消除逆序对，每次最多只能消除一组逆序对，因此必须执行$O(n^2)$级的交换次数，这就是为什么冒泡、插入、选择算法只能到$O(n^2)$级的原因。反过来说，基于交换元素的排序算法要想突破$O(n^2)$级，必须通过一些比较，交换间隔比较远的元素，使得一次交换能消除一个以上的逆序对



### 堆排序

堆排序基于堆的数据结构，需要用到两个堆中重要的操作：

- 构建堆
- 调整堆，使其仍满足堆的定义

构建堆有两种方式：

1. 依次向一个空堆中插入所有元素
2. 将整个数组初始状态视作完全二叉树，自底向上调整树的结构

将堆用于排序也要求我们数组索引从0开始使用，而不是1，此时完全二叉树具有如下性质：

- 对于第$i$个数，其左孩子的索引为$left=2i+1$，右孩子的索引为$right=left+1$
- 有$n$个元素的完全二叉树，最后一个非叶子节点的下标为$\frac{n}{2}-1$



#### 实现代码

```c
void swap(int *arr, int i, int j) {
    int tmp;
    
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void maxHeapify(int *arr, int size, int index) {
    int max_index, left, right;
    
    max_index = index;
    left = (index << 1) + 1;
    right = left + 1;
    
	max_index = left < size && arr[left] > arr[max_index] ? left : max_index;
    max_index = right < size && arr[right] > arr[max_index] ? right : max_index;
    
    if(max_index != index) {
        swap(arr, index, max_index);
        maxHeapify(arr, size, max_index);
        // 递归，保证子树还是最大堆
    }  
}

void buildMaxHeap(int *arr, int size) {
    for(int i = (size >> 1) - 1; i >= 0; i--) {
        maxHeapify(arr, size, i);
    }
}

void heapSort(int *arr, int size) {
    buildMaxHeap(arr, size);
    
    for(int i = 0; i < size; i++) {
        swap(arr, 0, size-1-i);
        maxHeapify(arr, size-1-i, 0);
    }
}
```



#### 分析

堆排序不是稳定的算法

数学可以证明，采用第二种构建最大堆方式的时间复杂度是$O(n)$，而调整最大堆的时间复杂度是$O(nlogn)$，因此堆排序总的时间复杂度为$O(nlogn)$

空间复杂度为$O(1)$



### 快速排序

实际使用中是几个$O(nlogn)$排序中效率最高的，其基本思想为：

- 从数组中取出一个数，称之为基数(pivot)
- 遍历数组，将比基数大的数字放在其右边，比基数小的数字放在基数左边。遍历完成后，数组被分成两个区域
- 将左右两个区域视为两个数组，重复前两个步骤，直到排序完成

每一次排序都是将基数放在了正确的地方，第一轮放好1个，第二轮2个，第三轮4个，以此类推，但如果数组为空，则对于 基数无贡献，即为最坏的情况，因此时间复杂度为$O(nlogn)-O(n^2)$，平均时间复杂度为$O(nlogn)$

#### 快排的基本框架

依据思想，搭建基本框架：

```c
ElementType partition(ElementType *arr, Position start, Position end) {

}

void QuickSort(ElementType *arr, Position start, Position end, int (*compare)(ElementType a, ElementType b)) {
    int mid;

    mid = partition(arr, start, end);

    QuickSort(arr, start, mid-1, compare);
    QuickSort(arr, mid+1, end, compare);
}

void quickSort(ElementType *arr, int arrSize, int (*compare)(ElementType a, ElementType b)) {
    QuickSort(arr, 0, arrSize-1, compare);
}
```

#### 何时结束递归

当某个区域只剩一个数字或没有数字时，就应该结束继续递归

```c
void QuickSort(ElementType *arr, Position start, Position end, int (*compare)(ElementType a, ElementType b)) {
    int mid;

    if(start < end) {
        mid = partition(arr, start, end);

        QuickSort(arr, start, mid-1, compare);
        QuickSort(arr, mid+1, end, compare);
    }
}
```

但由于mid的计算方法，$start >= end$仅存在相等和差为1两种情况

#### 分区算法的实现

一般有三种选择选择基数(pivot)的方式:

- 选取第一个元素
- 选取最后一个元素
- 选取任意元素

其中第三种算法的平均时间复杂度最优，但实现的代码采用第一种方式

分区算法也存在着两种写法

```c
ElementType partition(ElementType *arr, Position start, Position end, int (*compare)(ElementType a, ElementType b)) {
    int pivot, left, right;

    pivot = arr[start];
    left = start + 1;
    right = end;

    while(left < right) {
        while(left < right && compare(arr[left], pivot) <= 0) {
            left += 1;
        }

        if(left != right) {
            ElementType tmp;

            tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;

            right -= 1;
        }
    }

    if(left == right && compare(arr[right], pivot) > 0) {
        right -= 1;
    }
    if(right != start) {
        ElementType tmp;

        tmp = arr[start];
        arr[start] = arr[right];
        arr[right] = tmp;
    }

    return right;
}
```

更为常见的是下面这种写法：

```c
ElementType partition(ElementType *arr, Position start, Position end, int (*compare)(ElementType a, ElementType b)) {
    int pivot;
    Position left, right;
    ElementType tmp;

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
```

#### 分析

排序算法并**不是稳定的排序算法**

时间复杂度为$O(nlogn)-O(n^2)$，平均为$O(nlogn)$，空间复杂度为$O(logn)-O(n)$，平均为$O(logn)$

快排最坏的情况就是选取第一个元素作为pivot，但是数组本身有序，为了避免这一问题，可以做如下优化

- 选取随机元素作为pivot
- 将原数组顺序打乱
- 对于数组是否有序做判断

实践来看，将1、3两种方法结合使用，仅在数组较大时，判断原数组是否有虚



### 归并排序

#### 合并两个有序列表

充分利用两列表有序，在时间复杂度为$O(n)$的条件下实现合并

```c
int* merge(int *arr1, int size1, int *arr2, int size2) {
    int *arr, ptr1, ptr2, ptr;
    
    arr = (int*)malloc(sizeof(int)*(size1+size2));
    ptr = ptr1 = ptr2 = 0;
    
    while(ptr1 < size1 || ptr2 < size2) {
        if(ptr1 < size1 && ptr2 < size2) {
            if(arr1[ptr1] <= arr2[ptr2]) {
                arr[ptr++] = arr1[ptr1++];
            }
            else {
                arr[ptr++] = arr2[ptr2++];
            }
        }
        else if(ptr1 < size1) {
            arr[ptr++] = arr1[ptr1++];
        }
        else {
            arr[ptr++] = arr2[ptr2++];
        }
    }
    
    return arr;
}
```

#### 将原数组递归拆分

能够这么做的原因是一元数组一定有序

#### 归并实现排序

```c
void merge(int *arr, int start, int end, int *res) {
    int end1, start2, ptr1, ptr2, ptr;
    
    end1 = (end-start) / 2 + start;
    start2 = end1 + 1;
    
    ptr = ptr1 = start; ptr2 = start2;
    while(ptr1 <= end1 || ptr2 <= end) {
        if(ptr1 <= end1 && ptr2 <= end) {
            if(arr[ptr1] <= arr[ptr2]) {
                res[ptr++] = arr[ptr1++];
            }
            else {
                res[ptr++] = arr[ptr2++];
            }
        }
        else if(ptr1 <= end1) {
            res[ptr++] = arr[ptr1++];
        }
        else {
            res[ptr++] = arr[ptr2++];
        }
    }
    
    for(ptr = start; ptr <= end; ptr++) {
        arr[ptr] = res[ptr];
    }
}

void MergeSort(int *arr, int start, int end, int *res) {
    int mid;
    
    if(end > start) {
        mid = (end-start) / 2 + start;
        
        MergeSort(arr, start, mid, res);
        MergeSort(arr, mid+1, end, res);
        
        merge(arr, start, end, res);
    }
}

void mergeSort(int *arr, int size) {
    int *res;
    
    if(size <= 1) {
        return ;
    }
    
    res = (int*)malloc(sizeof(int)*size);
    
    MergeSort(arr, 0, size-1, res);
    
    free(res);
}
```

**反复分配再释放临时的空间时间和内存开销都非常大**，因此从始至终公用一个临时数组是最好的办法。



#### 分析

**是否存在原地归并排序？**

如果不借助其他内存空间，我们需要对merge函数做一定的修改：

- 方式一：仍旧双指针遍历两个数组，将index1和index2两个指针指向的较小值放在index1的位置。如果这个数是index1所指向的，则不需要移动数组，只要index1右移即可；但若是index2则需要将[index1, index2)的所有元素有意一个单位，并将值放入index1的位置，index1、index2同时右移一次，相应的标识左数组结尾的end1也需要右移一个单位
- 方式二：这种方式不改变左右两数组的尺寸，我们总是将index1和index2指向的较小值交换到index1的位置，调整交换到右数组值的位置，仍需保证右数组有序

无论哪种方式，都只是借用了归并排序递归的思想，实际时间复杂度都达到了$O(n^2)$，效率很低

**复杂度**

时间复杂度为$\varTheta(nlogn)$，空间复杂度为$\varTheta(n)$

**稳定性**

merge函数中的$\le$保证了归并排序算法的稳定性

```c
if(ptr1 <= end1 && ptr2 <= end)
```



## 时间复杂度为$O(n)$的排序算法

### 计数排序

计数排序的核心就是对一定范围的数据排序。

#### 伪计数排序

如果需要对一列数组排序，这个数组中每个元素都是$[1,9]$区间内的整数。那么我们可以构建一个长度为$9$的数组用于计数，计数数组的下标分别对应区间内的9个整数。然后遍历待排序的数组，将区间内每个整数出现的次数统计到计数数组中对应下标的位置。最后遍历计数数组，将每个元素输出，输出的次数就是对应位置记录的次数。

算法非常简单，用于纯数学排序也不存在问题，但用这种方式排序，我们无法得到属于原对象的任何信息。比如对于商品价格进行排序，我们只能拿到排序的结果，却不再知道某个价格对应什么商品

#### 伪计数排序2.0

为了解决上面的问题，我们可以将计数的数组换为一个能够存储对象的队列数组，最后输出时利用队列的FIFO特性还可以保证排序的稳定性

#### 真 计数排序

理论上计数排序可以适用于任何整形指标的排序，计数排序的执行流程为：

1. 遍历数组，确定最大值max和最小值min，并开辟大小为$max-min+1$的count数组
2. 遍历数组，统计范围内各值出现的数目
3. 将count数组内转化为索引所对应的元素下标
4. 开辟等大的额外数组，将数组按照count记录的索引进行放置，并时刻调整记录的索引值
5. 将额外数组的值写回原数组

有多种方式完成步骤3，我们采用效率更高的倒序遍历，实现代码如下：

```c
typedef int ElementType;

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
```

#### 分析

最后的倒序遍历保证了排序算法的**稳定性**

时间、空间复杂度均为$O(n+k)$，$k$表示数据范围的大小

因此，计数排序只适用于那些数据范围跨度不大的整形数组（或对象的整形属性）

处理仅有一位的小数，可以使用$\times 10$的办法

> 计数排序之所以可以突破$O(nlogn)$的限制，是因为其并不是基于比较，而是基于数组本身的属性

基于比较的排序最好的时间复杂度为$O(nlogn)$



### 基数排序

基数排序和计数排序类似，只能处理整数的数组，基本思想类似于对日期进行排序，先对年进行排序，再对月排序，最后对日排序。对于一个整数数组运用这种思想，逐位比较基数的大小，循环最大数字位数轮后，即可完成排序。依据基数的顺序，可以分为

- 最高位优先法MSD
- 最低位优先发LSD

一般而言LSD排序的方式更为常用，但相应的要求对于基数的排序必循采用稳定算法，而MSD则可以不采用稳定的排序算法

基数排序的流程分为三个步骤：

- 找出数组中最大的数字位数maxDigitLength
- 获取数组中每个数字的基数
- 遍历maxDigitLength轮数组，每轮按照基数对其进行排序

对于任意的整数，找出最大的数字位数可以通过绝对值最大的数进行获取

```c
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
```

获取基数后，应该采用稳定的排序算法，且可以取到的值仅有$-9—9$（负数是为了解决非负整数而设计），采用计数排序，完整代码如下：

```c
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
```

这里是一个一般的情况，即对于任意整数进行排序，如果只是对于非负整数进行排序，还可以取得更高的效率

**MSD的操作十分复杂**，不再赘述

#### 分析

空间复杂度与计数排序相同，均为$O(n+k)$，对于非负整数排序$k=10$，任意整数则是$k=19$

时间复杂度为$O(d(n+k))$，$d$为最长的数字位数



### 桶排序

桶排序的思想是：

- 将区间划分为$n$个相同大小的子区间，每个子区间称为一个桶
- 遍历数组，将每个数字装入桶中
- 对每个桶内的数字单独排序，这里需要采用其他排序算法，如插入、归并、快排等
- 最后按照顺序将所有桶内的数字合并起来

桶排序的高效基于数据均匀分布在各个区间，在分布极度不均时，只是徒增了外层循环，因此在桶排序问题中需要关注两个问题：

- **桶的数量**：桶的数量过少，会导致单个桶内的数字过多，桶排序的时间复杂度就会在很大程度上受桶内排序算法的影响。桶的数量过多，占用的内存就会较大，并且会出现较多的空桶，影响遍历桶的效率
- **桶的数据结构：**如果将桶的数据结构设置为数组，那么每个桶的长度必须设置为待排序数组的长度，因为我们需要做好最坏的打算，即所有的数字都被装入了同一个桶中，所以这种方案的空间复杂度会很高。而使用链表有一个好处，即所有桶的总长度刚好等于待排序数组的长度，不会造成内存浪费，但链表排序相较于数组难以操作，且开销更大

桶排序的执行流程：

1. 遍历数组找到数组的最大值和最小值，并设置桶的数量

2. 遍历数组，将每个数据按照划分装桶
3. 对于每个桶内的数据进行排序，借助其他排序算法
4. 将每个桶中的数据整合回原数组

当使用**数组**作为数据结构时，每个桶都需要和原数组等大，造成了大量的空间浪费，使用动态数组又会增加很多额外的**时间开销**，相当于以时间换空间；而使用链表作为数据结构，虽然可以节约空间，但对于链表的排序会很耗时；可以采用折中的方式，装桶时用链表，排序时用数组，但是将链表转化为数组会增加额外的$O(n)$的时间复杂度和空间复杂度，因此总结如下：

- 以数组作为桶，初始化每个桶的长度为$n$：时间上做到了最好，但空间占用很高
- 以数组作为桶，初始化每个桶的长度为$0$：空间上做到了最好，但装桶时对数组扩容比较耗时
- 以链表作为桶：空间上做到了最好，并且装桶时无需扩容，但对链表排序比较耗时
- 装桶时采用链表，排序时采用数组：时间和空间上都是一种折中的方案，但 链表 转换数组的过程需要遍历一次数组，增加了$O(n)$的时间，转换后会占用$O(n)$的空间

#### 分析

在满足均匀分布的前提下，时间复杂度为$O(n)$，空间复杂度与数据结构有关，若采用后三种方式为$O(n)$

桶排序相较于之前的两种线性时间复杂度的排序，是第一个可以用于浮点数的排序，但均匀分布的条件也相对较为ke'ke



