#ifndef __BT_H__
#define __BT_H__

#include <stdio.h>

typedef int ElementType;

typedef struct TreeNode *PtrToTNode;
struct TreeNode {
    PtrToTNode left, right;
    ElementType val;
};
typedef PtrToTNode Tree;

void preOrderTraversalByRecursion(Tree t) {
    if(t) {
        printf("%d ", t->val);

        preOrderTraversalByRecursion(t->left);
        preOrderTraversalByRecursion(t->right);
    }
}

void inOrderTraversalByRecursion(Tree t) {
    if(t) {
        inOrderTraversalByRecursion(t->left);

        printf("%d ", t->val);

        inOrderTraversalByRecursion(t->right);
    }
}

void postOrderTraversalByRecursion(Tree t) {
    if(t) {
        postOrderTraversalByRecursion(t->left);
        postOrderTraversalByRecursion(t->right);

        printf("%d ", t->val);
    }
}

#endif