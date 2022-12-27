#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int KeyType;
typedef int ValType;
typedef int Position;

typedef struct SetNode *PtrToSetNode;
struct SetNode {
    KeyType key;
    PtrToSetNode next;
};
typedef PtrToSetNode SetList;

typedef struct {
   SetList *buckets;
   int size; 
} HashSet;

Position HashFunc(KeyType key) {
	return key % 1000 + 999;
}

HashSet *makeNewHashSet(int size) {
	HashSet *newHashSet;

	newHashSet = (HashSet*)malloc(sizeof(HashSet));
	newHashSet->size = size;
	newHashSet->buckets = (PtrToSetNode*)malloc(sizeof(struct SetNode)*size);
	memset(newHashSet->buckets, 0, sizeof(PtrToSetNode)*size);

	return newHashSet;
}

bool HashSetContains(HashSet *s, KeyType key) {
	bool isContained;
	PtrToSetNode ptr;

	isContained = false;
	ptr = (s->buckets)[HashFunc(key)];

	while(ptr) {
		if(ptr->key == key) {
			isContained = true;
			break;
		}
        ptr = ptr->next;
	}

	return isContained;
}

void HashSetAdd(HashSet *s, KeyType key) {
	PtrToSetNode ptr;

	if(!HashSetContains(s, key)) {
		ptr = (s->buckets)[HashFunc(key)];
		(s->buckets)[HashFunc(key)] = (PtrToSetNode)malloc(sizeof(struct SetNode));
		(s->buckets)[HashFunc(key)]->key = key;
		(s->buckets)[HashFunc(key)]->next = ptr;
	}
}

void HashSetRemove(HashSet *s, KeyType key) {
	PtrToSetNode ptr, tmp;
    
    if(HashSetContains(s, key)) {
        ptr = (s->buckets)[HashFunc(key)];
        if(ptr->key == key) {
            (s->buckets)[HashFunc(key)] = ptr->next;
            free(ptr);
        }
        else {
            tmp = (s->buckets)[HashFunc(key)];
            ptr = ptr->next;
            while(ptr) {
                if(ptr->key == key) {
                    tmp->next = ptr->next;
                    free(ptr);
                    break;
                }
                tmp = ptr;
                ptr = ptr->next;
            }
        }
    }
}

void HashSetFree(HashSet* s) {
    PtrToSetNode ptr1, ptr2;
    
    for(int i = 0; i < s->size; i++) {
        if((s->buckets)[i] != NULL) {
            ptr1 = (s->buckets)[i];
            while(ptr1) {
                ptr2 = ptr1->next;
                free(ptr1);
                ptr1 = ptr2;
            }
        }
    }

    free(s);
}

typedef struct MapNode *PtrToMapNode;
struct MapNode {
    KeyType key;
    ValType val;
    PtrToMapNode next;
};
typedef PtrToMapNode MapList;

typedef struct {
    MapList *buckets;
    int size;
} HashMap;

HashMap *makeNewHashMap(int size) {
    HashMap *newHashMap;

    newHashMap = (HashMap*)malloc(sizeof(HashMap));
    newHashMap->size = size;
    newHashMap->buckets = (MapList*)malloc(sizeof(struct MapNode)*size);
    memset(newHashMap->buckets, 0, sizeof(PtrToMapNode)*size);

    return newHashMap;
}

bool HashMapContains(HashMap *m, KeyType key) {
    PtrToMapNode ptr;
    bool contain;

    contain = false;
    ptr = (m->buckets)[HashFunc(key)];
    while(ptr) {
        if(ptr->key == key) {
            contain = true;
            break;
        }
        ptr = ptr->next;
    }

    return contain;
}

ValType HashMapGet(HashMap* m, KeyType key) {
    PtrToMapNode ptr;
    ValType val;

    ptr = (m->buckets)[HashFunc(key)];
    while(ptr) {
        if(ptr->key == key) {
            val = ptr->val;
            break;
        }
        ptr = ptr->next;
    }

    return val;
}

void HashMapPut(HashMap* m, KeyType key, ValType value) {
    PtrToMapNode ptr;
    
    ptr = (m->buckets)[HashFunc(key)];
    if(HashMapContains(m, key)) {
        while(ptr) {
            if(ptr->key == key) {
                ptr->val = value;
                break;
            } 
            ptr = ptr->next;
        }
    }
    else {
        (m->buckets)[HashFunc(key)] = (PtrToMapNode)malloc(sizeof(struct MapNode));
        (m->buckets)[HashFunc(key)]->next = ptr;
        (m->buckets)[HashFunc(key)]->val = value;
        (m->buckets)[HashFunc(key)]->key = key;
    }
}

void HashMapRemove(HashMap *m, ValType key) {
    PtrToMapNode ptr1, ptr2;
    
    if(HashMapContains(m, key)) {
        ptr1 = (m->buckets)[HashFunc(key)];
        if(ptr1->key == key) {
            (m->buckets)[HashFunc(key)] = ptr1->next;
        }
        else {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
            while(ptr1) {
                if(ptr1->key == key) {
                    ptr2->next = ptr1->next;
                    free(ptr1);
                }
                ptr2 = ptr1;
                ptr1 = ptr1->next;
            }
        }
    }
}

void HashMapFree(HashMap* m) {
    PtrToMapNode ptr1, ptr2;

    for(int i = 0; i < m->size; i++) {
        if((m->buckets)[i] != NULL) {
            ptr1 = (m->buckets)[i];
            while(ptr1) {
                ptr2 = ptr1->next;
                free(ptr1);
                ptr1 = ptr2;
            }
        }
    }

    free(m);
}

#endif