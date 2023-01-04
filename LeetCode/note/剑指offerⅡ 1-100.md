# 剑指offerⅡ 1-100



## 36.后缀表达式(中等)

https://leetcode.cn/problems/8Zf90G/description/

```c
typedef int ElementType;
typedef int Position;

typedef struct {
    ElementType *stackArr;
    Position top;
    int capacity;
} Stack;

Stack *makeNewStack(int size) {
    Stack *newStack;

    newStack = (Stack*)malloc(sizeof(Stack));
    newStack->top = -1;
    newStack->stackArr = (ElementType*)malloc(sizeof(ElementType)*size);
    newStack->capacity = size;

    return newStack;
}

bool isEmptyStack(Stack *s) {
    return s->top == -1;
}

bool isFullStack(Stack *s) {
    return s->top + 1 == s->capacity;
}

void push(Stack *s, ElementType val) {
    if(!isFullStack(s)) {
        (s->stackArr)[++s->top] = val;
    }
    else {
        printf("Stack is full!\n");
        abort();
    }
}

ElementType pop(Stack *s) {
    if(isEmptyStack(s)) {
        printf("Stack is empty!\n");
        abort();
    }
    
    return (s->stackArr)[(s->top)--];
}

ElementType getTopEle(Stack *s) {
    if(isEmptyStack(s)) {
        printf("Stack is empty!\n");
        abort();
    }
    
    return (s->stackArr)[s->top];
}

void freeStack(Stack *s) {
    free(s->stackArr);
    free(s);
}

bool isDigitStr(char *str) {
    return !(strlen(str) == 1 && (str[0] > '9' || str[0] < '0'));
}

int strToInt(char *str) {
    int num;

    num = 0;

    if(str[0] == '-') {
        for(int i = 1; str[i]; i++) {
            num = num*10 + str[i] - '0';
        }
        num *= -1;
    }
    else {
        for(int i = 0; str[i]; i++) {
            num = num*10 + str[i] - '0';
        }
    }

    return num;
}

int evalRPN(char ** tokens, int tokensSize){
    Stack *s;
    int num1, num2, res;

    s = makeNewStack(tokensSize);

    for(int i = 0; i < tokensSize; i++) {
        if(isDigitStr(tokens[i])) {
            push(s, strToInt(tokens[i]));
        }
        else {
            num2 = pop(s);
            num1 = pop(s);

            switch(tokens[i][0]) {
                case '+': push(s, num1+num2); break;
                case '-': push(s, num1-num2); break;
                case '*': push(s, num1*num2); break;
                case '/': push(s, num1/num2); break;
            }
        }
    }

    res = pop(s);
    freeStack(s);

    return res;
}
```



## 43.往完全二叉树添加节点(中等)

https://leetcode.cn/problems/NaqhDT/description/

```c
typedef struct TreeNode* ElementType;
typedef int Position;

typedef struct {
    ElementType *queueArr;
    Position head, tail;
    int capacity;
} Queue;

Queue *makeNewQueue(int size) {
    Queue *newQueue;

    newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->queueArr = (ElementType*)malloc(sizeof(ElementType)*(size+1));
    newQueue->capacity = size + 1;
    newQueue->head = newQueue->tail = 0;

    return newQueue;
}

bool isEmptyQueue(Queue *q) {
    return (q->head % q->capacity) == (q->tail % q->capacity);
}

bool isFullQueue(Queue *q) {
    return (q->head % q->capacity) == ((q->tail+1) % q->capacity);
}

void enQueue(Queue *q, ElementType val) {
    if(isFullQueue(q)) {
        printf("Queue is full!\n");
        abort();
    }

    (q->queueArr)[(++(q->tail))%(q->capacity)] = val;
}

ElementType deQueue(Queue *q) {
    if(isEmptyQueue(q)) {
        printf("Queue is empty!\n");
        abort();
    }

    return (q->queueArr)[(++(q->head))%(q->capacity)];
}

ElementType getHeadEle(Queue *q) {
    if(isEmptyQueue(q)) {
        printf("Queue is empty!\n");
        abort();
    }

    return (q->queueArr)[q->head%q->capacity];
}

int elementNumInQueue(Queue *q) {
    int eleNum;
    
    if(q->tail%q->capacity > q->head%q->capacity) {
        eleNum = q->tail%q->capacity - q->head%q->capacity;
    }
    else if(q->tail%q->capacity == q->head%q->capacity) {
        eleNum = 0;
    }
    else {
        eleNum = q->tail%q->capacity - q->head%q->capacity + q->capacity-1;
    }

    return eleNum;
}

void freeQueue(Queue *q) {
    free(q->queueArr);
    free(q);
}

typedef struct {
    struct TreeNode* node_ptr_arr[11001];
    int node_count;
} CBTInserter;


CBTInserter* cBTInserterCreate(struct TreeNode* root) {
    CBTInserter *obj;
    Queue *q;
    int num_in_queue;
    struct TreeNode *ptr;

    obj = (CBTInserter*)malloc(sizeof(CBTInserter));
    memset(obj->node_ptr_arr, 0, sizeof(struct TreeNode*)*11001);
    obj->node_count = 0;

    if(root) {
        q = makeNewQueue(10000);
        enQueue(q, root);
        while(!isEmptyQueue(q)) {
            num_in_queue = elementNumInQueue(q);

            for(int i = 0; i < num_in_queue; i++) {
                ptr = deQueue(q);
                (obj->node_ptr_arr)[++(obj->node_count)] = ptr;

                if(ptr->left) {
                    enQueue(q, ptr->left);
                }
                if(ptr->right) {
                    enQueue(q, ptr->right);
                }
            }
        }
    }

    return obj;
}

int cBTInserterInsert(CBTInserter* obj, int val) {
    int retVal;

    (obj->node_ptr_arr)[++(obj->node_count)] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    (obj->node_ptr_arr)[obj->node_count]->val = val;
    (obj->node_ptr_arr)[obj->node_count]->left = NULL;
    (obj->node_ptr_arr)[obj->node_count]->right = NULL;
    
    if(obj->node_count % 2 == 0) {
        (obj->node_ptr_arr)[obj->node_count/2]->left = (obj->node_ptr_arr)[obj->node_count];
    }
    else {
        (obj->node_ptr_arr)[obj->node_count/2]->right = (obj->node_ptr_arr)[obj->node_count];
    }
    
    retVal = (obj->node_ptr_arr)[obj->node_count/2]->val;

    return retVal;
}

struct TreeNode* cBTInserterGet_root(CBTInserter* obj) {
    return (obj->node_ptr_arr)[1];
}

void cBTInserterFree(CBTInserter* obj) {
    free(obj);
}
```

