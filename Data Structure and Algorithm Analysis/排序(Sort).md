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
            if(arr1[ptr1] <= arr[ptr2]) {
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

