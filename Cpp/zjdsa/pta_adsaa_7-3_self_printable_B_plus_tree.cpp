#include<iostream>
#include<queue>
using namespace std;

constexpr int kMaxLen = 5, kMaxKey = 3, kMaxPtr = 4;

typedef int KeyType;
typedef struct Node *TreePtr;
struct Node {
    int n = 0;
    bool isLeaf = true;
    KeyType keys[kMaxLen] = {-1, -1, -1, -1, -1};
    TreePtr parent = nullptr;
    TreePtr ptrs[kMaxLen] = {0, 0, 0, 0, 0};
};

class BTree {
public:
    BTree();
    ~BTree();
    TreePtr search(KeyType key, int &idx);
    void insert(KeyType key);
    void self_print();
private:
    void _split(TreePtr x);
    
    TreePtr root = nullptr;
};

int main(){
    sizeof(Node);
    freopen("E:\\in.txt", "r", stdin);
    // ios::sync_with_stdio(false);
    int N, keyin;
    cin >> N;
    BTree btree;
    for (int i = 0; i < N; ++i){
        cin >> keyin;
        btree.insert(keyin);
    }
    btree.self_print();
    return 0;
}

BTree::BTree(){
    root = new Node;
}

BTree::~BTree(){
    queue<TreePtr> que;
    if (root) que.push(root);
    while (!que.empty()){
        TreePtr crt = que.front();
        que.pop();
        if (!crt->isLeaf){
            for (int i = 0; i <= crt->n; ++i)
                que.push(crt->ptrs[i]);
        }
        delete crt;
    }
}

TreePtr BTree::search(KeyType key, int &idx){
    idx = -1;
    TreePtr ptr = root;
    while (ptr){
        if (ptr->isLeaf){
            for (idx = 1; idx <= ptr->n; ++idx)
                if (ptr->keys[idx] == key)
                    return ptr;
            idx = -1;
            return ptr;
        }
        idx = ptr->n;
        while (key < ptr->keys[idx]) --idx;//key is all positive;
        ptr = ptr->ptrs[idx];
    }
    return ptr;
}


void BTree::insert(KeyType key){
    int idx = -1;
    TreePtr ptr = search(key, idx);
    if (idx == -1){
        for (idx = ptr->n; key < ptr->keys[idx]; --idx)
            ptr->keys[idx + 1] = ptr->keys[idx];
        ptr->keys[idx + 1] = key;
        ++ptr->n;
        if (ptr->n == kMaxPtr)//ptr has to be a leaf node;
            _split(ptr);
    }
    else cout << "Key " << key << " is duplicated" << endl;
    return;
}

void BTree::_split(TreePtr x){
    TreePtr z = new Node;
    int i = x->n;//i == 4 if isLeaf; i == 3 if nonLeaf;
    for (; i > 2; --i, --x->n, ++z->n){
        z->keys[i - 2] = x->keys[i];
        z->ptrs[i - 2] = x->ptrs[i];
    }
    z->ptrs[i - 2] = x->ptrs[i];//i == 2;
    if (x == root){
        TreePtr r = new Node;
        r->isLeaf = false;
        if (x->isLeaf){
            r->keys[1] = x->keys[3];
            // z->keys[2] = x->keys[4];
            // z->keys[1] = x->keys[3];
            // x->n = z->n = 2;
        }
        else {
            z->isLeaf = false;
            r->keys[1] = x->keys[2];
            // z->keys[1] = x->keys[3];
            // z->ptrs[0] = x->ptrs[2];
            // z->ptrs[1] = x->ptrs[3];
            // x->n = z->n = 1;
        }
        r->ptrs[0] = x;
        r->ptrs[1] = z;
        r->n = 1;
        x->parent = z->parent = r;
        root = r;
        return;
    }
    int shift_up = x->isLeaf ? x->keys[3] : x->keys[2];
    TreePtr p = x->parent;
    i = p->n;
    for (; shift_up < p->keys[i]; --i)
        p->keys[i + 1] = p->keys[i];
    p->keys[i + 1] = shift_up;
    p->ptrs[i + 1] = z;
    z->parent = p;
    ++p->n;
    if (p->n == kMaxKey) _split(p);    
    // if (x->isLeaf){
    //     // z->keys[2] = x->keys[4];
    //     // z->keys[1] = x->keys[3];
    //     TreePtr p = x->parent;
    //     int i = p->n;
    //     for (; z->keys[1] < p->keys[i]; --i)
    //         p->keys[i + 1] = p->keys[i];
    //     p->keys[i + 1] = z->keys[1];
    //     p->ptrs[i + 1] = z;
    //     z->parent = p;
    //     //z->n has increased;
    //     ++p->n;
    //     if (p->n == kMaxKey) _split(p);
    // }
    // else {//x is an interior node;
    //     z->isLeaf = false;
    //     // z->keys[1] = x->keys[3];
    //     // z->ptrs[0] = x->ptrs[2];
    //     // z->ptrs[1] = x->ptrs[3];
    //     TreePtr p = x->parent;
    //     int i = p->n;
    //     for (; x->keys[2] < p->keys[i]; --i){
    //         p->keys[i + 1] = p->keys[i];
    //         p->ptrs[i + 1] = p->ptrs[i];
    //     }
    //     p->keys[i + 1] = x->keys[2];
    //     p->ptrs[i + 1] = z;
    //     z->parent = p;
    //     //z->n has increased;
    //     ++p->n;
    //     if (p->n == kMaxKey) _split(p);
    // }
    return;
}

void BTree::self_print(){
    queue<TreePtr> que;
    TreePtr last = root, tail = root;
    if (root) que.push(root);
    while (!que.empty()){
        TreePtr crtP = que.front();
        que.pop();
        cout << "[";
        for (int i = 0; i <= crtP->n; ++i){
            if (i){
                if (i != 1) cout << ",";
                cout << crtP->keys[i];
            }
            if (!crtP->isLeaf && crtP->ptrs[i])
                que.push(last = crtP->ptrs[i]);
        }
        cout << "]";
        if (crtP == tail) {
            cout << endl;
            tail = last;
        }
    }
    return;
}