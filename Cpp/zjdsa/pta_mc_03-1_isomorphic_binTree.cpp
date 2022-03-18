#include<cstdio>
using namespace std;

class BTNode {
    friend class BinTree;
public:
    BTNode(){}
    BTNode& operator=(const BTNode& bt){
        data = bt.data;
        lchild = bt.lchild;
        rchild = bt.rchild;
        return *this;
    }
private:
    char data;
    int lchild = -1, 
        rchild = -1;
};

class BinTree {
public:
    using Tree = BTNode*;
    BinTree(int sz)
        :size(sz), tree(new BTNode[size + 2])
    {
        insert();
    }
    ~BinTree(){
        delete[] tree;
    }
    void insert(){
        char lfIn, rtIn;
        for (int i = 0;i < size; ++i){
            scanf("%c %c %c ", &tree[i].data, &lfIn, &rtIn);
            tree[i].lchild = (int)(lfIn - '0');
            tree[i].rchild = (int)(rtIn - '0');
        }
    }
    bool isomorphic(const BinTree& bt){
        if (size != bt.size) return false;
        BTNode tarNode, cmpNode;
        for (int i = 0;i < size; ++i){
            tarNode = tree[i];
            int j;
            for (j = 0; j < bt.size; ++j){
                if (bt.tree[j].data == tarNode.data){
                    cmpNode = bt.tree[j];
                    break;
                }
            }
            if (j == bt.size) return false;
            /*compare*/
            char tarChild[2]{}, cmpChild[2]{};
            if (tarNode.lchild >= 0) tarChild[0] = tree[tarNode.lchild].data;
            if (tarNode.rchild >= 0) tarChild[1] = tree[tarNode.rchild].data;
            if (cmpNode.lchild >= 0) cmpChild[0] = bt.tree[cmpNode.lchild].data;
            if (cmpNode.rchild >= 0) cmpChild[1] = bt.tree[cmpNode.rchild].data;
            
            bool flag;
            for(j = 0; j < 2; ++j){
                for (int k = 0; k < 2; ++k){
                    if (tarChild[j] != cmpChild[k]) flag = false;
                    else {
                        flag = true;
                        break;
                    }
                }
                if (!flag) return false;
            }
        }
        return true;
    }
private:
    int size;
    Tree tree;
};

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    int N;
    scanf("%d ", &N);
    BinTree tree1 {N};
    scanf("%d ", &N);
    BinTree tree2 {N};
    if (tree1.isomorphic(tree2))
        printf("Yes");
    else printf("No");
    return 0;
}