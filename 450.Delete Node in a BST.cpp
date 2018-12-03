题意：删除二叉搜索树中值等于指定值的结点。
方法一：递归
思路：
1.首先需要找到值等于目标值的结点，如果不存在，返回空。
2.找到之后需要判断该结点是否左右结点都存在，如果其中一个不存在，直接将root结点移动到存在的一方即可。
注意每次递归都需要用上一次的根连接，便于连接删除结点之后的子树。
3.如果左右结点都存在，那么则需要找到该结点右子树中的最小结点，即比当前结点值大的最小结点值，赋值给当前遍历到的结点。
接着递归删除当前结点右子树中值等于被交换值的结点，使其满足二叉搜索树。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root) return NULL;
        if(root -> val > key){
            root -> left = deleteNode(root -> left,key);
        }else if(root -> val < key){
            root -> right = deleteNode(root -> right,key);
        }else{
            if(!root -> left || !root -> right){
                root = (root -> left) ? root -> left : root -> right;
            }else{
                TreeNode *cur = root -> right;
                while(cur -> left) cur = cur -> left;
                root -> val = cur -> val;
                root -> right = deleteNode(root -> right,cur -> val);
            }
        }
        return root;
    }
};

方法二：迭代
1.迭代需要记录下遍历到的结点的前一个结点，因此设置一个pre == NULL,每次进入循环之后首先把pre = cur,再移动cur.
2.找到key之后break,如果不存在pre,说明删除根结点，如果不存在cur,说明没有找到，直接返回root,注意先判断cur再判断pre.
能找到目标元素之后，pre需要判断目标结点在左侧还是右侧，连接上后删除cur结点。
3.在删除方法中，如果本身已经是叶子结点，直接返回NULL
如果左不存在或者右不存在，那么返回存在的一侧
如果左右都存在，用当前结点替换右子树中的最左侧结点，同样记录pre和cur.如果pre位置不变，那么用根的右等于cur的右侧。
如果pre位置变了，那么pre的左为cur的右，即删除cur结点。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode *pre = NULL;
        TreeNode *cur = root;
        while(cur){
            if(cur -> val == key) break;
            pre = cur;
            if(cur -> val > key) cur = cur ->left;
            else cur = cur -> right;
        }
        if(!cur) return root;
        if(!pre) return del(cur);
        if(pre -> left && pre -> left -> val == key) pre -> left = del(cur);
        else pre -> right = del(cur);
        return root;
    }
    
    TreeNode* del(TreeNode* root){
        if(!root->left && !root -> right) return NULL;
        if(!root -> left || !root -> right){
            return root -> left ? root -> left : root -> right;
        }
        
        TreeNode *pre = root;
        TreeNode *cur = pre -> right;
        while(cur -> left) {
            pre = cur;
            cur = cur -> left;
        }
        root -> val = cur -> val;
        (pre == root ? root -> right : pre -> left) = cur -> right;
        return root;
        
    }
};

方法3:删除二叉树中某个结点的通用方法
1.递归找目标结点，如果找到了，与它右子树中的最小值结点的值进行交换，再进入递归。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root) return NULL;
        if(root -> val == key){
            if(!root -> right) return root -> left;
            else{
                TreeNode *cur = root -> right;
                while(cur -> left) cur = cur -> left;
                swap(root-> val,cur -> val);
            }
        }
        root -> left = deleteNode(root->left ,key);
        root -> right = deleteNode(root -> right,key);
        return root;
    }
};
