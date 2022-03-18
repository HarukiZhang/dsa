typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
} TreeNode;

void middle_order(TreeNode *Node) {
    if(Node != NULL) {
        middle_order(Node->left);
        printf("%d ", Node->data);
        middle_order(Node->right);
    }
}
 