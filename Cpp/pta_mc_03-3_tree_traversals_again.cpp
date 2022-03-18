#include<iostream>
using namespace std;

/*
The order of stack push-pop of inorder traversal, is its preorder traversal order;
*/

constexpr int kMaxNodeNum = 30;

class TNode {
    friend class BinTree;
private:
    int lchild, rchild;
};

class BinTree {
public:
    using Tree = TNode;
    BinTree(int sz) : size(sz){}
    void reconstruct();
    void traversal_post();
private:
    Tree tree[kMaxNodeNum + 2]{};//if no child, ptr = 0;
    int size;
    int entry;
};

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    int N;
    cin >> N >> ws;
    BinTree bTree {N};
    bTree.reconstruct();
    bTree.traversal_post();
    return 0;
}

void BinTree::reconstruct(){
    /*the key is to distinguish 
        which side of subtree is under the current operation of push;
    This can be known from the type of last operation:
    When current operation is "push":
        if last opt == "push", then the node under pushing is a left subtree;
        if last opt == "pop" , then the node under pushing is a right subtree;
    */
    int *stack = new int [size + 2], top = -1;
    char command[5]{ 0, 0 }, lastCmd;
    int popNode, data;
    for (int i = 0; i < 2*size; ++i){
        lastCmd = command[1];
        cin >> command >> ws;
        if (command[1] == 'u'){//"push";
            cin >> data >> ws;

            if (lastCmd == 'o')//last command == "pop";
                tree[popNode].rchild = data;
            else {//last command == "push" or the crt push is the first opt;
                if (lastCmd == 0)//if the fisrt push;
                    entry = data;
                else tree[stack[top]].lchild = data;
            }
            stack[++top] = data;
        }
        else//crt command == "pop";
            popNode = stack[top--];
    }
    return;
}

void BinTree::traversal_post(){
    bool firstTime = true;
    int *stack = new int [size + 2], top = -1;
    int last, crt = entry;
    while (crt != 0 || top >= 0){
        while (crt != 0){
            stack[++top] = crt;
            crt = tree[crt].lchild;
        }
        crt = stack[top];
        /*suspend to pop;*/
        if (tree[crt].rchild == 0 || last == tree[crt].rchild){
            /*if crt node has no rchild OR just return from a rchild;*/
            if (firstTime) firstTime = false;
            else cout << " ";
            cout << crt << flush;//visit current node;
            --top;
            last = crt;
            crt = 0;
        }
        /*when crt node has a rchild AND it has yet been visited;*/
        else crt = tree[crt].rchild;
    }
    delete[] stack;
    return;
}


/*example of non-rec level traversal;
void traversal_inorder(BinTree N){
    
    typename BinTree crt = N;
    while (crt || !stack.empty()){
        while (crt){
            stack.push(crt);
            crt = crt->lchild;
        }
        if (!stack.empty()){
            crt = stack.pop();
            visit(crt);
            crt = crt->rchld;
        }
    }
}
*/