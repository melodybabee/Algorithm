题意：在BST中返回等于目标值的根结点及其子树
方法一：递归
思路：
1.不存在根结点返回空，目标值等于根结点返回根结点
2.否则根据左右结点与目标结点的大小值来判断应该向哪一侧递归
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
    TreeNode* searchBST(TreeNode* root, int val) {
        if(!root) return NULL;
        if(root -> val == val) return root;
        if(root -> val > val) return searchBST(root -> left, val);
        else  return searchBST(root -> right, val);
    }
};
方法2:迭代
思路：
当根结点存在或者不等于目标值的时候继续进行循环，否则返回根结点
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
    TreeNode* searchBST(TreeNode* root, int val) {
        while(root && root -> val != val){
            root = root -> val > val ? root -> left : root -> right;
        }
        return root;
    }
};