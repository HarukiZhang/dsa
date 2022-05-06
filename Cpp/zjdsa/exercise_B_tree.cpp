#include<iostream>
#include<utility>
#include<queue>
using namespace std;

constexpr int kMinDeg = 2, kMaxKey = 2 * kMinDeg - 1, kMaxPtr = kMaxKey + 1;

typedef int KeyType;
typedef struct BTNode *TreePtr;

struct BTNode {
    int n = 0;
    bool isLeaf = true;
    KeyType keys[kMaxKey] = {};
    TreePtr ptrs[kMaxPtr] = {};
};

class BTree {
public:
    BTree();
    ~BTree();
    pair<TreePtr, int> search(KeyType k);
    void insert(KeyType k);
    void erase(KeyType k);
    void traversal();
private:
    void _split(TreePtr x, int i);
    void _insert_nonFull(TreePtr x, KeyType k);
    //merge i-th key of sat AND all keys of sal INTO dest;
    void _merge(TreePtr dest, TreePtr sat, int i, TreePtr sal);
    void _erase_recur(TreePtr x, KeyType k);//to erase key k from node x;
    void _erase_key(TreePtr x, int i);//designate to erase i-th key of node x;

    int size = 0, height = 0;
    TreePtr root = nullptr;
};

int main(){
    BTree T;

    T.erase('P');//testing empty tree erasing;

    T.insert('F');
    T.erase('F');//erase to empty;

    T.insert('F');
    T.insert('S');
    T.insert('Q');
    T.insert('K');
    T.insert('C');
    T.insert('L');
    T.insert('H');
    T.insert('T');
    T.insert('V');
    T.insert('W');
    T.traversal(); cout << endl;

    T.erase('W');//direct erasing;
    cout << "direct erase W in a leaf node:" << endl;
    T.traversal(); cout << endl;
    T.erase('T');//merge two children;
    cout << "erase T : merge two children => goto new-merged-child to erase T:" << endl;
    T.traversal(); cout << endl;
    
    T.insert('W');
    T.insert('T');
    //reinsert W and T;
    T.insert('M');
    T.insert('R');
    T.insert('N');
    T.insert('P');
    T.insert('A');
    T.insert('B');
    cout << "insert some new keys:" << endl;
    T.traversal(); cout << endl;

    T.erase('F');
    cout << "erase F : merge two children THEN borrow from left child : " << endl;
    T.traversal(); cout << endl;
    T.erase('M');//borrow from right child;
    cout << "erase M : borrow from right child : " << endl;
    T.traversal(); cout << endl;
    T.erase('L');
    cout << "erase L : merge md to lf and goto lf to erase L:" << endl;
    T.traversal(); cout << endl;

    T.insert('Y');
    T.insert('Z');
    T.erase('S');
    T.erase('T');
    cout << "preparation for erasing R:" << endl;
    T.traversal(); cout << endl;

    T.erase('R');
    cout << "erase R : borrow from right brother : " << endl;
    T.traversal(); cout << endl;

    T.insert('F');
    T.insert('M');
    cout << "re-insert F and M:" << endl;
    T.traversal(); cout << endl;

    T.erase('G');//delete a non-exist key;
    cout << "try to erase a non-exist key G, structure was changed:" << endl;
    T.traversal(); cout << endl;
    
    // T.insert('P');
    // T.insert('A');
    // T.insert('B');
    // T.insert('X'); T.traversal(); cout << endl;
    // T.insert('Y');
    // T.insert('D');
    // T.insert('Z');
    // T.insert('E'); T.traversal(); cout << endl;
    return 0;

}

void BTree::_erase_key(TreePtr x, int i){
    //if the key to be erased is the last key, no need to move any key,
    //just decresing x->n will suffice;
    while (++i < x->n){
        x->keys[i - 1] = x->keys[i];
        x->ptrs[i] = x->ptrs[i + 1];
    }
    --x->n;
    return;
}

void BTree::_erase_recur(TreePtr x, KeyType k){
    int i = 0;//i for keys;
    while (i < x->n && k >= x->keys[i]) ++i;
    int j = i--;//j for ptrs;
    if (i >= 0 && x->keys[i] == k){//if k is within x;
        if (x->isLeaf){
            _erase_key(x, i);
            --size;
            //root node space can not be deleted;
        }
        else {//x is an internal node;
            TreePtr y = x->ptrs[j - 1];//nodes less than k;
            TreePtr z = x->ptrs[j];//nodes equal or greater than k;
            if (y->n >= kMinDeg){//if the subnode before i has at-least kMinDeg keys;
                x->keys[i] = y->keys[y->n - 1];//substitute i in x with the last key in y;
                //recursively erase the last key in y;
                _erase_recur(y, y->keys[y->n - 1]);
            }
            else {
                if (z->n >= kMinDeg){
                    x->keys[i] = z->keys[0];
                    _erase_recur(z, z->keys[0]);
                }
                else {
                    //merge i-th key of x (key k) and all keys of z into y;
                    _merge(y, x, i, z);
                    //z should be deleted within _merge;
                    //key k was inserted into y when merging;
                    _erase_recur(y, k);//recursively erase key k from y;
                }
            }
        }
    }
    else {//if k is without x, but within sub-tree succeeded x;
        //if x is leaf but k is still not in it, k is not in the tree;
        if (x->isLeaf) return;
        TreePtr md = x->ptrs[j];
        TreePtr lf, rt = lf = nullptr;
        if (md->n < kMinDeg){
            //borrow key from siblings;
            i = i >= 0 ? i : 0;//force i to be valid;
            if (j - 1 >= 0 && (lf = x->ptrs[j - 1])->n >= kMinDeg){
                //make space in md;
                md->ptrs[md->n + 1] = md->ptrs[md->n];
                int iMd = md->n;//substitute the last key of md;
                while (--iMd >= 0){
                    md->keys[iMd + 1] = md->keys[iMd];
                    md->ptrs[iMd + 1] = md->ptrs[iMd];
                }//space maked;
                //tri-nodes exchanging;
                md->keys[0] = x->keys[i];//down-shift the i-th key of node x;
                md->ptrs[0] = lf->ptrs[lf->n];//the last ptr of lf node;
                x->keys[i] = lf->keys[lf->n - 1];//the last key of lf node;
                //one plus one minus: causes no size change;
                ++md->n;
                --lf->n;
            }
            else if (j + 1 <= x->n && (rt = x->ptrs[j + 1])->n >= kMinDeg){
                int iMd = md->n;//insert after all keys of md;
                //because j + 1 <= x->n, i + 1 is valid;
                //down-shift (i+1)-th key TO node md after all its keys;
                md->keys[md->n] = x->keys[i + 1];
                md->ptrs[md->n + 1] = rt->ptrs[0];//the 1st ptr of rt;
                x->keys[i + 1] = rt->keys[0];//the 1st key of rt;
                //make space in rt;
                int iRt = 0;
                while (++iRt < rt->n){//actualy starting move from index 1;
                    rt->keys[iRt - 1] = rt->keys[iRt];
                    rt->ptrs[iRt - 1] = rt->ptrs[iRt];
                }
                rt->ptrs[iRt - 1] = rt->ptrs[iRt];//space maked;
                //one plus one minus: causes no size change;
                ++md->n;
                --rt->n;
            }
            else {//three of brothers all has less than kMinDeg keys;
                if (lf != nullptr){
                    //merge i-th key of x and all keys of md into lf;
                    _merge(lf, x, i, md);
                    md = lf;//for uniformity of calling of _erase_recur();
                }
                else {//if lf == nullptr, then rt wont be nullptr;
                    //merge i-th key of x and all keys of rt into md;
                    _merge(md, x, i, rt);
                    //md is still md;
                }
            }
        }
        //the key k is either in the md, or
        //the key k has been moved into lf, and md == lf;
        _erase_recur(md, k);
    }
    return;
}

void BTree::erase(KeyType k){
    if (root->n != 0)//non-empty tree;
        _erase_recur(root, k);
    return;
}

BTree::BTree(){
    root = new BTNode;
    /*DISK_WRITE(root);*/
}

BTree::~BTree(){
    queue<TreePtr> que;
    if (root) que.push(root);
    while (!que.empty()){
        TreePtr crt = que.front();
        que.pop();
        if (!crt->isLeaf){//ensure only valid ptr will be pushed;
            for (int i = 0; i <= crt->n; ++i)
                que.push(crt->ptrs[i]);
        }
        delete crt;
    }
    //root will be deleted within while-loop;
}

pair<TreePtr, int> BTree::search(KeyType k){
    TreePtr p = root;
    while (true){
        int i = 0;
        while (i < p->n && p->keys[i] < k) ++i;
        if (i < p->n && p->keys[i] == k)
            return {p, i};
        else if (p->isLeaf)
            return {nullptr, -1};
        else {
            /*DISK_READ(p, ptrs[i]);*/
            p = p->ptrs[i];
        }
    }
}

void BTree::insert(KeyType k){
    TreePtr r = root;
    if (r->n == kMaxKey){
        root = new BTNode;
        //newNode.n = 0, by default;
        root->isLeaf = false;
        root->ptrs[0] = r;
        _split(root, 0);
        ++height;//spliting the root is only way for height increment;
    }
    _insert_nonFull(root, k);
    return;
}

void BTree::_merge(TreePtr dest, TreePtr sat, int i, TreePtr sal){
    //sat: static node; sal : src_whose_all_keys_being_transferred;
    //uniformly move right node into left node, so that all keys just simply
    //be inserted after (on right side of) dest's own keys;
    int &iD = dest->n;
    dest->keys[iD++] = sat->keys[i];
    _erase_key(sat, i);
    //moving all keys of sal to dest;
    int iA = 0;
    while (iA < sal->n){
        dest->keys[iD] = sal->keys[iA];
        dest->ptrs[iD] = sal->ptrs[iA];
        ++iD;
        ++iA;
    }
    dest->ptrs[iD] = sal->ptrs[iA];
    //deal with root changing;
    if (sat == root && sat->n == 0) {
        root = dest;//change root;
        --height;
        delete sat;
    }
    delete sal;//after merging, sal is always needed to delete;
    return;
}

void BTree::_split(TreePtr x, int i){
    //x : father, y : who is full;
    TreePtr z = new BTNode;
    TreePtr y = x->ptrs[i];
    int j = kMinDeg;//for y;
    int k = 0;//for z;
    for (; j < y->n; ++j, ++k){
        z->keys[k] = y->keys[j];
        z->ptrs[k] = y->ptrs[j];
    }
    z->ptrs[k] = y->ptrs[j];//the last ptr of y;
    z->isLeaf = y->isLeaf;
    z->n = y->n = kMinDeg - 1;
    //set x;
    j = x->n - 1;//for keys;
    k = x->n;//for ptrs;
    for (; k > i; --j, --k){
        x->keys[j + 1] = x->keys[j];
        x->ptrs[k + 1] = x->ptrs[k];
    }
    x->keys[j + 1] = y->keys[kMinDeg - 1];
    x->ptrs[k + 1] = z;
    ++x->n;
    /*DISK_WRITE(y);*/
    /*DISK_WRITE(z);*/
    /*DISK_WRITE(x);*/
    return;
}

void BTree::_insert_nonFull(TreePtr x, KeyType k){
    int i = x->n - 1;
    if (x->isLeaf){//insert into crt node;
        for (; i >= 0 && k < x->keys[i]; --i)
            x->keys[i + 1] = x->keys[i];
        x->keys[i + 1] = k;
        ++x->n;
        ++size;
        /*DISK_WRITE(x);*/
    }
    else {//x is not leaf;
        while (i >= 0 && k < x->keys[i]) --i;
        ++i;//the ptr at right side of the key belongs to the key;
        /*DISK_READ(x->ptrs[i]);*/
        //protection-if: every node on which this func being called would be non-full;
        if (x->ptrs[i]->n == kMaxKey){
            _split(x, i);
            //after split, x->keys[i] will be the median key of x->ptrs[i];
            if (k > x->keys[i])
                ++i;//if new key is better, goto new child;
        }
        _insert_nonFull(x->ptrs[i], k);//recursive descending;
        //tail recursion; it can be rewrited with loop;
    }
    return;
}

void BTree::traversal(){
    queue<TreePtr> que;
    TreePtr last, tail;
    int level = 0;
    if (root) {
        que.push(root);
        last = tail = root;
    }
    while (!que.empty()){
        TreePtr p = que.front();
        que.pop();

        int i = 0;

        if (!p->isLeaf){
            while (i <= p->n){
                que.push(last = p->ptrs[i++]);
            }
        }
        i = 0;
        while (i < p->n){
            cout << static_cast<char>(p->keys[i++]);
        }
        cout << "  ";

        if (p == tail){
            ++level;
            tail = last;
            cout << endl;
        }
    }
    return;
}