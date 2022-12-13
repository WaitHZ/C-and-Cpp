# 剑指offer 1-100



## 3.数组中重复的数字(简单)

https://leetcode.cn/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/description/?favorite=xb9nqhhg

```c
int findRepeatNumber(int* nums, int numsSize){
    int *hash_table, index;

    hash_table = (int*)malloc(sizeof(int)*numsSize);

    for(int i = 0; i < numsSize; i++) {
        hash_table[i] = 0;
    }

    for(int i = 0; i < numsSize; i++) {
        if(hash_table[nums[i]] > 0) {
            index = i;

            break;
        }
        hash_table[nums[i]] += 1;
    }

    return nums[index];
}
```



## 5.替换空格(简单)

https://leetcode.cn/problems/ti-huan-kong-ge-lcof/description/?favorite=xb9nqhhg

```c
#define MAXN 30001

char* replaceSpace(char* s){
    char *newStr;
    int slow_ptr, fast_ptr;

    newStr = (char*)malloc(sizeof(char)*MAXN);
    slow_ptr = fast_ptr = 0;

    while(s[fast_ptr]) {
        if(s[fast_ptr] == ' ') {
            newStr[slow_ptr++] = '%';
            newStr[slow_ptr++] = '2';
            newStr[slow_ptr++] = '0';
            fast_ptr += 1;
        }
        else {
            newStr[slow_ptr++] = s[fast_ptr++];
        }
    }
    newStr[slow_ptr] = '\0';

    return newStr;
}
```



## 6.从尾到头打印链表(简单)

https://leetcode.cn/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/description/?favorite=xb9nqhhg

```c
struct SNode {
    int SArr[10000];
    int top;
};
typedef struct SNode *Stack;

Stack makeStack() {
    Stack new_stack;

    new_stack = (Stack)malloc(sizeof(struct SNode));
    new_stack->top = -1;

    return new_stack;
}

bool isEmptyStack(Stack s) {
    return s->top == -1;
}

void push(Stack s, int ele) {
    (s->SArr)[++(s->top)] = ele;
}

int pop(Stack s) {
    return (s->SArr)[(s->top)--];
}

int* reversePrint(struct ListNode* head, int* returnSize){
    int node_count, *retArr, index, ele;
    Stack s;

    s = makeStack();

    node_count = 0;
    index = 0;

    while(head) {
        push(s, head->val);
        head = head->next;
        node_count += 1;
    }

    retArr = (int*)malloc(sizeof(int)*node_count);
    while(!isEmptyStack(s)) {
        ele = pop(s);

        retArr[index++] = ele;
    }

    *returnSize = node_count;

    return retArr;
}
```



## 07.重建二叉树(中等)

https://leetcode.cn/problems/zhong-jian-er-cha-shu-lcof/description/?favorite=xb9nqhhg

```c
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    struct TreeNode *root;
    int index;
    int *left_preorder, *right_preorder, *left_inorder, *right_inorder;

    root = NULL;
    
    if(preorderSize > 0) {
        root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        root->val = preorder[0];

        for(int i = 0; i < inorderSize; i++) {
            if(inorder[i] == preorder[0]) {
                index = i;
                break;
            }
        }

        left_preorder = (int*)malloc(sizeof(int)*index);
        left_inorder = (int*)malloc(sizeof(int)*index);
        right_preorder = (int*)malloc(sizeof(int)*(inorderSize-index-1));
        right_inorder = (int*)malloc(sizeof(int)*(inorderSize-index-1));

        for(int i = 0; i < index; i++) {
            left_inorder[i] = inorder[i];
            left_preorder[i] = preorder[1+i];
        }

        for(int i = 0; i < inorderSize-index-1; i++) {
            right_inorder[i] = inorder[index+1+i];
            right_preorder[i] = preorder[index+1+i];
        }

        root->left = buildTree(left_preorder, index, left_inorder, index);
        root->right = buildTree(right_preorder, inorderSize-index-1, right_inorder, inorderSize-index-1);
    }

    return root;
}
```



## 10-Ⅰ.斐波那契数列(简单)

https://leetcode.cn/problems/fei-bo-na-qi-shu-lie-lcof/?favorite=xb9nqhhg

```c
int fibArr[101] = {0, 1, 1};

int fib(int n){
    int num;

    if(n <= 1) {
        num = fibArr[n];
    }
    else if(fibArr[n] > 0) {
        num = fibArr[n];
    }
    else {
        num = fib(n-1) + fib(n-2);
        fibArr[n] = num;
    }

    return num % 1000000007;
}
```



## 10-Ⅱ.青蛙跳台阶问题(简单)

https://leetcode.cn/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/description/?favorite=xb9nqhhg

```c
int arr[101] = {1, 1, 2};

int numWays(int n){
    int num;

    if(n <= 2) {
        num = arr[n];
    }
    else if(arr[n] > 0) {
        num = arr[n];
    }
    else {
        num = numWays(n-1) + numWays(n-2);
        arr[n] = num;
    }

    return num % 1000000007;
}
```



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



## 51.数组中的逆序对(困难)

https://leetcode.cn/problems/shu-zu-zhong-de-ni-xu-dui-lcof/description/

```c
int merge(int *arr, int start, int end, int *res) {
    int end1, start2, ptr1, ptr2, ptr, count;
    
    end1 = (end-start) / 2 + start;
    start2 = end1 + 1;
    count = 0;
    
    ptr = ptr1 = start; ptr2 = start2;
    while(ptr1 <= end1 || ptr2 <= end) {
        if(ptr1 <= end1 && ptr2 <= end) {
            if(arr[ptr1] <= arr[ptr2]) {
                res[ptr++] = arr[ptr1++];
            }
            else {
                res[ptr++] = arr[ptr2++];

                count += (end1-ptr1+1);
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

    return count;
}

int MergeSort(int *arr, int start, int end, int *res) {
    int mid, numLeft, numRight, numCross;

    numLeft = numRight = numCross = 0;
    
    if(end > start) {
        mid = (end-start) / 2 + start;
        
        numLeft = MergeSort(arr, start, mid, res);
        numRight = MergeSort(arr, mid+1, end, res);
        
        numCross = merge(arr, start, end, res);
    }

    return numLeft + numRight + numCross;
}

int reversePairs(int* nums, int numsSize){
    int *res, numPairs;
    
    if(numsSize <= 1) {
        return 0 ;
    }
    
    res = (int*)malloc(sizeof(int)*numsSize);
    
    numPairs = MergeSort(nums, 0, numsSize-1, res);
    
    free(res);

    return numPairs;
}
```

