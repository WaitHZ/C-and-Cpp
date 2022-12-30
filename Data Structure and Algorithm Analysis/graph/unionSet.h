// root = (int*)malloc(sizeof(int)*size);
// rank = (int*)malloc(sizeof(int)*size);

void init(int *root, int *rank, int size) {
    for(int i = 0; i < size; i++) {
        root[i] = i;
        rank[i] = 1;
    }
}

int find(int *root, int ind) {
    int r;
    
    r = ind;
    
    if(ind != root[ind]) {
        r = find(root, root[ind]);
        root[ind] = r;
    }
    
    return r;
}

void union_by_rank(int *root, int *rank, int ind1, int ind2) {
    int root1, root2;
    
    root1 = find(root, ind1);
    root2 = find(root, ind2);
    
    if(root1 != root2) {
        if(rank[root1] > rank[root2]) {
            root[root2] = root1;
        }
        else if(rank[root1] < rank[root2]) {
            root[root1] = root2;
        }
        else {
            root[root2] = root1;
            rank[root1] += 1;
        }
    }
}

bool isConnected(int *root, int ind1, int ind2) {
    return find(root, ind1) == find(root, ind2);
}