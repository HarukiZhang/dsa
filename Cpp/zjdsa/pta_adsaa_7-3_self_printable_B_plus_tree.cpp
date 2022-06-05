#include<iostream>
#include<queue>
using namespace std;

constexpr int kMaxLen = 10010, kMinDeg = 2, kMaxKey = 3, kMaxPtr = 4;

typedef int KeyType;
typedef struct Node *TreePtr;
struct Node {
    int n = 0;
    bool isLeaf = true;
    KeyType keys[kMaxPtr] = {-1, -1, -1, -1};
    TreePtr ptrs[kMaxPtr] = {0, 0, 0, 0};
};

class BTree {
public:
    BTree();
    ~BTree();
    void insert(KeyType key);
    void self_print();
private:
    void _split(TreePtr x, int i);
    void _insert_nonFull(TreePtr x, KeyType key);
    
    TreePtr root = nullptr;
};

int main(){
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

void BTree::insert(KeyType key){
    TreePtr r = root;
    if (r->n == kMaxKey){
        root = new Node;
        root->isLeaf = false;
        root->ptrs[0] = r;
        _split(root, 0);
    }
    _insert_nonFull(root, key);
    return;
}

void BTree::_split(TreePtr x, int i){
    TreePtr z = new Node;
    TreePtr y = x->ptrs[i];
    z->keys[1] = y->keys[3];
    z->ptrs[0] = y->ptrs[2];
    z->ptrs[1] = y->ptrs[3];
    for (int j = x->n; j > i; --j){
        x->keys[j + 1] = x->keys[j];
        x->ptrs[j + 1] = x->ptrs[j];
    }
    x->keys[i + 1] = y->keys[2];//i max to 2;
    x->ptrs[i + 1] = z;
    ++x->n;
    y->n = z->n = 1;
    return;
}
/*
if x->n == 0 && i == 0 : 
    transfer y[2] to x[1];

if x->n == 1 && i == 0 : 
    move x[1] to x[2]; 
    transfer y[2] to x[1];

if x->n == 1 && i == 1 : 
    transfer y[2] to x[2];
    
if x->n == 2 && i == 0 : 
    move x[2] to x[3]; 
    move x[1] to x[2]; 
    transfer y[2] to x[1];

if x->n == 2 && i == 1 : 
    move x[2] to x[3]; 
    transfer y[2] to x[2];

if x->n == 2 && i == 2 : 
    transfer y[2] to x[3];
*/

void BTree::_insert_nonFull(TreePtr x, KeyType key){
    while (true){
        int i = x->n;
        if (x->isLeaf){
            for (int j = 1; j <= x->n; ++j)
                if (x->keys[j] == key){
                    cout  << "Key " << key << " is duplicated" << endl;
                    break;
                }
            for (; i >= 1 && key < x->keys[i]; --i)
                x->keys[i + 1] = x->keys[i];
            x->keys[i + 1] = key;
            ++x->n;
            break;
        }
        while (i >= 1 && key < x->keys[i]) --i;
        if (i != 0 && key == x->keys[i]){
            cout << "Key " << key << " is duplicated" << endl;
            break;
        }
        if (x->ptrs[i]->n == kMaxKey){
            _split(x, i);
            if (key >= x->keys[i + 1])
                ++i;
        }
        x = x->ptrs[i];
    }
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
            if (crtP->ptrs[i])
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