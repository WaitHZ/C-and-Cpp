# LeetCode



## 14.最长的公共前缀

https://leetcode.cn/problems/longest-common-prefix/description/

```c
char * longestCommonPrefix(char ** strs, int strsSize) {
    char *min_str, *max_str;
    int index;

    min_str = max_str = strs[0];

    for(int i = 1; i < strsSize; i++) {
        if(strcmp(min_str, strs[i]) > 0) {
            min_str = strs[i];
        }
        if(strcmp(max_str, strs[i]) < 0) {
            max_str = strs[i];
        }
    }

    for(index = 0; index < strlen(min_str); index++) {
        if(max_str[index] != min_str[index])
            break;
    }

    min_str[index] = '\0';

    return min_str;
}
```

巧妙地借助了字典序。



## 19. 删除链表的倒数第 N 个结点

https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/

```c
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode *ptr, *tmp_ptr;
    int node_count, n_in_order;

    ptr = head;
    node_count = 0;

    while(ptr) {
        node_count += 1;
        ptr = ptr->next;
    }
    n_in_order = node_count - n + 1;

    if(n_in_order == 1) {
        tmp_ptr = head;
        head = head ->next;

        free(tmp_ptr);
    }
    else {
        ptr = head;
        for(int i = 0; i < n_in_order-2; i++)
            ptr = ptr->next;

        tmp_ptr = ptr->next;
        ptr->next = tmp_ptr ? tmp_ptr->next : NULL;

        free(tmp_ptr);
    }

    return head;
}
```



## 26.删除有序数组中的重复项(简单)

https://leetcode.cn/problems/remove-duplicates-from-sorted-array/description/

### 解法1：暴力求解

```c
int removeDuplicates(int* nums, int numsSize) {
    for(int i = 1; i < numsSize; i++) {
        if(nums[i] == nums[i-1]) {
            for(int j = i; j < numsSize-1; j++) {
                nums[j] = nums[j+1];
            }
            numsSize -= 1;
            i -= 1;
        }
    }

    return numsSize;
}
```

### 解法2：双指针法

```c
int removeDuplicates(int* nums, int numsSize) {
    int fast_ptr, slow_ptr;

    slow_ptr = fast_ptr = 1;

    while(fast_ptr < numsSize) {
        if(nums[fast_ptr] != nums[fast_ptr-1]) {
            nums[slow_ptr++] = nums[fast_ptr];
        }

        fast_ptr += 1;
    }

    return slow_ptr;
}
```

双指针一块一慢，保证一次遍历就可以实现，时间复杂度为$O(n)$.



## 27. 移除元素

https://leetcode.cn/problems/remove-element/description/

```c
int removeElement(int* nums, int numsSize, int val){
    int slow_ptr, fast_ptr;

    slow_ptr = fast_ptr = 0;

    while(fast_ptr < numsSize) {
        if(nums[fast_ptr] != val) {
            nums[slow_ptr++] = nums[fast_ptr];
        }

        fast_ptr += 1;
    }

    return slow_ptr;
}
```

双指针，时间复杂度为$O(n)$.



## 28.找出字符串中第一个匹配项的下标

https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/description/

```c
int strStr(char * haystack, char * needle) {
    int slow_ptr, fast_ptr, in_needle;

    if(strlen(haystack) < strlen(needle))
        return -1;
    else if(strlen(needle) == 1) {
        for(int i = 0; i < strlen(haystack); i++)
        {
            if(haystack[i] == needle[0])
                return i;
        }

        return -1;
    }

    slow_ptr = fast_ptr = 0;
    in_needle = 0;

    while(fast_ptr < strlen(haystack)) {
        if(in_needle) {
            if(haystack[fast_ptr] == needle[fast_ptr-slow_ptr] && haystack[fast_ptr] != '\0')
                fast_ptr += 1;
            else {
                slow_ptr += 1;
                fast_ptr = slow_ptr;
                in_needle = 0;
            }
        }
        else {
            if(haystack[fast_ptr] == needle[0])
                in_needle = 1;
            else
                slow_ptr = ++fast_ptr;
        }

        if(haystack[fast_ptr] == needle[fast_ptr-slow_ptr] && fast_ptr-slow_ptr+1 == strlen(needle))
            break;
    }

    if(fast_ptr == strlen(haystack)) {
        fast_ptr -= 1;
    }

    return fast_ptr-slow_ptr+1 != strlen(needle) ? -1 : slow_ptr;
}
```



## 94.二叉树的中序遍历(简单)

https://leetcode.cn/problems/binary-tree-inorder-traversal/

### 解法1：递归实现

```c
int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
    int left_size, right_size, *left_sub_tree, *right_sub_tree, *retArr, index;

    if(root == NULL) {
        *returnSize = 0;
        return NULL;
    } 
    else {
        left_sub_tree = inorderTraversal(root->left, &left_size);
        right_sub_tree = inorderTraversal(root->right, &right_size);
        
        *returnSize = 1 + left_size + right_size;
        retArr = (int*)malloc(sizeof(int)*(*returnSize));
        
        for(index = 0; index < left_size; index++)
            retArr[index] = left_sub_tree[index];
        retArr[index++] = root -> val;
        for(int i = 0; i < right_size; i++)
            retArr[index+i] = right_sub_tree[i];

        return retArr;
    }
}
```

### 解法2：迭代实现

借助栈和一个tag实现迭代遍历。

```c
#define MAXN 100

struct RNode {
    struct TreeNode *root;
    int is_first;
};
typedef struct RNode *PtrToRNode;

struct SNode {
    PtrToRNode SArr[MAXN];
    int top;
};
typedef struct SNode *Stack;

Stack makeStack() {
    Stack new_stack;

    new_stack = (Stack)malloc(sizeof(struct SNode));

    new_stack->top = -1;

    return new_stack;
}

void pushStack(Stack s, PtrToRNode ptr) {
    s->SArr[++s->top] = ptr;
}

PtrToRNode popStack(Stack s) {
    return s->SArr[s->top--];
}

int isEmptyStack(Stack s) {
    if(s->top == -1)
        return 1;
    else
        return 0;
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    Stack s;
    PtrToRNode root_node, new_root_node;
    int *retArr;

    retArr = NULL;
    *returnSize = 0;

    if(root) {
        *returnSize = 0;
        retArr = (int*)malloc(sizeof(int)*100);

        s = makeStack();

        if(root->right) {
            root_node = (PtrToRNode)malloc(sizeof(struct RNode));
            root_node->root = root->right;
            root_node->is_first = 1;

            pushStack(s, root_node);
        }
        
        root_node = (PtrToRNode)malloc(sizeof(struct RNode));
        root_node->root = root;
        root_node->is_first = 0;
        pushStack(s, root_node);

        if(root->left) {
            root_node = (PtrToRNode)malloc(sizeof(struct RNode));
            root_node->root = root->left;
            root_node->is_first = 1;

            pushStack(s, root_node);
        }

        while(!isEmptyStack(s)) {
            root_node = popStack(s);

            if(root_node->is_first == 0) {
                retArr[(*returnSize)++] = root_node->root->val;

                free(root_node);
            }
            else {
                if(root_node->root->right) {
                    new_root_node = (PtrToRNode)malloc(sizeof(struct RNode));
                    new_root_node->root = root_node->root->right;
                    new_root_node->is_first = 1;

                    pushStack(s, new_root_node);
                }

                root_node->is_first = 0;
                pushStack(s, root_node);

                if(root_node->root->left) {
                    new_root_node = (PtrToRNode)malloc(sizeof(struct RNode));
                    new_root_node->root = root_node->root->left;
                    new_root_node->is_first = 1;

                    pushStack(s, new_root_node);
                }
            }
        }
    }

    return retArr;
}
```



## 98.验证二叉搜索树(中等)

https://leetcode.cn/problems/validate-binary-search-tree/description/

```c
int getMax(struct TreeNode* root) {
    struct TreeNode *ptr;
    int max_val;

    ptr = root;

    while(ptr) {
        max_val = ptr->val;
        ptr = ptr->right;
    }

    return max_val;
}

int getMin(struct TreeNode *root) {
    struct TreeNode *ptr;
    int min_val;

    ptr = root;

    while(ptr) {
        min_val = ptr->val;
        ptr = ptr->left;
    }

    return min_val;
}

bool isValidBST(struct TreeNode* root) {
    bool retBool;

    retBool = true;

    if(root) {
        if(!(isValidBST(root->left) && isValidBST(root->right))) {
            retBool = false;
        }
        else {
            if(root->left && root->right && !(root->val > getMax(root->left) && root->val < getMin(root->right)))
                retBool = false;
            else if(root->left && getMax(root->left) >= root->val)
                retBool = false;
            else if(root->right && getMin(root->right) <= root->val)
                retBool = false;
        }
    }

    return retBool;
}
```





## 101.对称二叉树(简单)

https://leetcode.cn/problems/symmetric-tree/description/

```c
bool isReversed(struct TreeNode *root1, struct TreeNode *root2) {
    bool retBool;

    retBool = false;

    if(root1 == NULL && root2 == NULL)
        retBool = true;
    else if(root1 == NULL || root2 == NULL)
        ;
    else if(root1->val == root2->val) {
        return isReversed(root1->left, root2->right) && isReversed(root1->right, root2->left);
    }

    return retBool;
}

bool isSymmetric(struct TreeNode* root) {
    return isReversed(root->left, root->right);
}
```



## 102.二叉树的层序遍历(中等)

https://leetcode.cn/problems/binary-tree-level-order-traversal/description/

```c
struct RNode {
    struct TreeNode *root;
    int layer;
};
typedef struct RNode *PtrToRNode;

struct QNode {
    PtrToRNode QArr[2000];
    int font, end;
};
typedef struct QNode *Queue;

Queue makeQueue() {
    Queue new_q;

    new_q = malloc(sizeof(struct QNode));

    new_q->font = new_q->end = 0;

    return new_q;
}

bool isEmptyQueue(Queue q) {
    return q->end == q->font ? true : false;
}

void enQueue(Queue q, PtrToRNode ptr) {
    q->QArr[++q->end] = ptr;
}

PtrToRNode deQueue(Queue q) {
    return q->QArr[++q->font];
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    int **retArr;
    Queue q;
    PtrToRNode tree_node, new_tree_node;

    retArr = NULL;

    *returnSize = 0;
    
    if(root == NULL)
        *returnColumnSizes = NULL;
    else {
        retArr = (int**)malloc(sizeof(int*)*2000);
        *returnColumnSizes = (int*)malloc(sizeof(int)*2000);

        for(int i = 0; i < 2000; i++) {
            retArr[i] = NULL;
            (*returnColumnSizes)[i] = 0;
        }

        q = makeQueue();

        tree_node = (PtrToRNode)malloc(sizeof(struct RNode));
        tree_node->root = root;
        tree_node->layer = 0;
        enQueue(q, tree_node);

        while(!isEmptyQueue(q)) {
            tree_node = deQueue(q);

            (*returnColumnSizes)[tree_node->layer] += 1;

            retArr[tree_node->layer] = realloc(retArr[tree_node->layer], sizeof(int)*((*returnColumnSizes)[tree_node->layer]));

            retArr[tree_node->layer][(*returnColumnSizes)[tree_node->layer]-1] = tree_node->root->val;

            if(tree_node->root->left) {
                new_tree_node = (PtrToRNode)malloc(sizeof(struct RNode));
                new_tree_node->root = tree_node->root->left;
                new_tree_node->layer = tree_node->layer + 1;

                enQueue(q, new_tree_node);
            }

            if(tree_node->root->right) {
                new_tree_node = (PtrToRNode)malloc(sizeof(struct RNode));
                new_tree_node->root = tree_node->root->right;
                new_tree_node->layer = tree_node->layer + 1;

                enQueue(q, new_tree_node);
            }

            *returnSize = tree_node->layer + 1 > *returnSize ? tree_node->layer + 1 : *returnSize;
            free(tree_node);
        }
    }

    return retArr;
}
```

一个重要却容易被忽视的内容：

![](./img/优先级.jpg)

解引用的运算优先级低于[]，所以需要对下面的代码加以区分：

```c
*Arr[size];
(*Arr)[size];
```



## 104.二叉树的最大深度(简单)

https://leetcode.cn/problems/maximum-depth-of-binary-tree/description/

```c
int maxDepth(struct TreeNode* root){
    int max_depth, left_depth, right_depth;

    max_depth = 0;

    if(root) {
        left_depth = maxDepth(root->left);
        right_depth = maxDepth(root->right);

        max_depth = left_depth > right_depth ? left_depth + 1 : right_depth + 1;
    }

    return max_depth;
}
```





## 108.将有序数组转换为二叉搜索树(简单)

https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/description/

```c
struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    struct TreeNode *root;
    int *left_sub_arr, *right_sub_arr;

    root = NULL;

    if(numsSize > 0) {
        root = (struct TreeNode*)malloc(sizeof(struct TreeNode));

        root->val = nums[numsSize/2];

        left_sub_arr = (int*)malloc(sizeof(int)*(numsSize/2));
        right_sub_arr = (int*)malloc(sizeof(int)*(numsSize-1-numsSize/2));

        memcpy(left_sub_arr, nums, sizeof(int)*(numsSize/2));
        memcpy(right_sub_arr, &nums[numsSize/2+1], sizeof(int)*(numsSize-1-numsSize/2));

        root->left = sortedArrayToBST(left_sub_arr, numsSize/2);
        free(left_sub_arr);
        root->right = sortedArrayToBST(right_sub_arr, numsSize-1-numsSize/2);
        free(right_sub_arr);
    }

    return root;
}
```



## 110.平衡二叉树(简单)

https://leetcode.cn/problems/balanced-binary-tree/description/

```c
int getTreeHeight(struct TreeNode *root) {
    int height;

    height = 0;
    
    if(root)
        height = getTreeHeight(root->left) > getTreeHeight(root->right) ? 1+getTreeHeight(root->left) : 1+getTreeHeight(root->right);

    return height;
}

bool isBalanced(struct TreeNode* root) {
    bool retBoolean;

    retBoolean = true;
    
    if(root)
        if(!(isBalanced(root->left) && isBalanced(root->right)) || fabs(getTreeHeight(root->left)-getTreeHeight(root->right)) > 1)
        retBoolean = false;

    return retBoolean;
}
```





## 111.二叉树的最小深度(简单)

https://leetcode.cn/problems/minimum-depth-of-binary-tree/description/

```c
void preOrderTraverse(struct TreeNode *root, int *min_depth, int layer) {
    if(root) {
        if(root->left || root->right) {
            preOrderTraverse(root->left, min_depth, layer+1);
            preOrderTraverse(root->right, min_depth, layer+1);
        }
        else
            *min_depth = *min_depth > layer ? layer : *min_depth;
    }
}

int minDepth(struct TreeNode* root){
    int min_depth;

    min_depth = 10000;

    preOrderTraverse(root, &min_depth, 1);

    if(!root)
        min_depth = 0;

    return min_depth;
}
```



## 112.路经总和(简单)

https://leetcode.cn/problems/path-sum/description/

```c
void pathTraverse(struct TreeNode* root, int path_sum, int targetSum, int *hasPath) {
    int sum;
    
    if(root && *hasPath == 0) {
        sum = path_sum + root->val;

        if(root->left == NULL && root->right == NULL) {
            if(sum == targetSum) 
                *hasPath = 1;
        }
        else {
            pathTraverse(root->left, sum, targetSum, hasPath);
            pathTraverse(root->right, sum, targetSum, hasPath);
        }
    }
}


bool hasPathSum(struct TreeNode* root, int targetSum) {
    int retVal;

    retVal = 0;

    pathTraverse(root, 0, targetSum, &retVal);

    return retVal == 1 ? true : false;
}
```

**需要注意C的关系并不依赖于缩进，else是与最近的未匹配的if进行匹配。**



## 144.二叉树的前序遍历(简单)

https://leetcode.cn/problems/binary-tree-preorder-traversal/description/

### 解法1：递归实现

```c
void preOrdTraverse(struct TreeNode* root, int *retArr, int *returnSize) {
    if(root) {
        retArr[(*returnSize)++] = root -> val;

        preOrdTraverse(root->left, retArr, returnSize);
        preOrdTraverse(root->right, retArr, returnSize);
    }
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int *retArr;

    *returnSize = 0;
    retArr = NULL;

    if(root) {
        retArr = (int*)malloc(sizeof(int)*100);

        preOrdTraverse(root, retArr, returnSize);
    }

    return retArr;
}
```

### 解法2：迭代实现

```c
struct TNode {
    struct TreeNode *root;
    int tag;
};
typedef struct TNode *PtrToTNode;

struct SNode {
    PtrToTNode SArr[100];
    int top;
};
typedef struct SNode *Stack;

Stack makeStack() {
    Stack new_stack;

    new_stack = (Stack)malloc(sizeof(struct SNode));

    new_stack->top = -1;

    return new_stack;
}

void pushStack(Stack s, PtrToTNode ptr) {
    s->SArr[++s->top] = ptr;
}

PtrToTNode popStack(Stack s) {
    return s->SArr[s->top--];
}

int isEmptyStack(Stack s) {
    if(s->top == -1)
        return 1;
    else
        return 0;
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int *retArr;
    PtrToTNode tree_node ,new_node;
    Stack s;

    s = makeStack();

    retArr = NULL;
    *returnSize = 0;
    
    if(root) {
        retArr = (int*)malloc(sizeof(int)*100);

        tree_node = (PtrToTNode)malloc(sizeof(struct TNode));

        tree_node->root = root;
        tree_node->tag = 1;

        pushStack(s, tree_node);
    }

    while(!isEmptyStack(s)) {
        tree_node = popStack(s);

        if(tree_node->tag) {
            if(tree_node->root->right) {
                new_node = (PtrToTNode)malloc(sizeof(struct TNode));

                new_node->tag = 1;
                new_node->root = tree_node->root->right;

                pushStack(s, new_node);
            }

            if(tree_node->root->left) {
                new_node = (PtrToTNode)malloc(sizeof(struct TNode));

                new_node->tag = 1;
                new_node->root = tree_node->root->left;

                pushStack(s, new_node);
            }

            tree_node->tag = 0;
            pushStack(s, tree_node);
        }
        else {
            retArr[(*returnSize)++] = tree_node->root->val;

            free(tree_node);
        }
    }

    return retArr;
}
```



## 145.二叉树的后序遍历(简单)

https://leetcode.cn/problems/binary-tree-postorder-traversal/description/

### 解法1：递归实现

```c
void postOrdTraverse(struct TreeNode* root, int *retArr, int *returnSize) {
    if(root) {
        postOrdTraverse(root->left, retArr, returnSize);
        postOrdTraverse(root->right, retArr, returnSize);
        
        retArr[(*returnSize)++] = root -> val;
    }
}

int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    int *retArr;

    *returnSize = 0;
    retArr = NULL;

    if(root) {
        retArr = (int*)malloc(sizeof(int)*100);

        postOrdTraverse(root, retArr, returnSize);
    }

    return retArr;

}
```

### 解法2：迭代实现

```c
struct TNode {
    struct TreeNode *root;
    int tag;
};
typedef struct TNode *PtrToTNode;

struct SNode {
    PtrToTNode SArr[100];
    int top;
};
typedef struct SNode *Stack;

Stack makeStack() {
    Stack new_stack;

    new_stack = (Stack)malloc(sizeof(struct SNode));

    new_stack->top = -1;

    return new_stack;
}

void pushStack(Stack s, PtrToTNode ptr) {
    s->SArr[++s->top] = ptr;
}

PtrToTNode popStack(Stack s) {
    return s->SArr[s->top--];
}

int isEmptyStack(Stack s) {
    if(s->top == -1)
        return 1;
    else
        return 0;
}

int* postorderTraversal(struct TreeNode* root, int* returnSize){
    int *retArr;
    PtrToTNode tree_node ,new_node;
    Stack s;

    s = makeStack();

    retArr = NULL;
    *returnSize = 0;
    
    if(root) {
        retArr = (int*)malloc(sizeof(int)*100);

        tree_node = (PtrToTNode)malloc(sizeof(struct TNode));

        tree_node->root = root;
        tree_node->tag = 1;

        pushStack(s, tree_node);
    }

    while(!isEmptyStack(s)) {
        tree_node = popStack(s);

        if(tree_node->tag) {
            tree_node->tag = 0;
            pushStack(s, tree_node);

            if(tree_node->root->right) {
                new_node = (PtrToTNode)malloc(sizeof(struct TNode));

                new_node->tag = 1;
                new_node->root = tree_node->root->right;

                pushStack(s, new_node);
            }

            if(tree_node->root->left) {
                new_node = (PtrToTNode)malloc(sizeof(struct TNode));

                new_node->tag = 1;
                new_node->root = tree_node->root->left;

                pushStack(s, new_node);
            }
        }
        else {
            retArr[(*returnSize)++] = tree_node->root->val;

            free(tree_node);
        }
    }

    return retArr;
}
```



