题意：计算完全二叉树的结点个数
方法一：正常递归
TLE
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
    int countNodes(TreeNode* root) {
        if(!root) return 0;
        int count = 1;
        helper(root,count);
        return count;
    }
    
    void helper(TreeNode* root, int &count){
        if(!root) return;
        if(root-> left){
            ++count;
            helper(root->left,count);
        }
        if(root -> right){
            ++count;
            helper(root -> right, count);
        }
    }
};
方法二：利用完全二叉树的性质
补充：
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
    int countNodes(TreeNode* root) {
        int left = leftHeight(root);
        int right = rightHeight(root);
        if(left == right) return pow(2,left)-1;
        return countNodes(root->left) + countNodes(root->right)+1;
    }
    int leftHeight(TreeNode* root){
        if(!root )return 0;
        return 1+leftHeight(root -> left);
    }
    int rightHeight(TreeNode* root){
        if(!root )return 0;
        return 1+rightHeight(root -> right);
    }
};