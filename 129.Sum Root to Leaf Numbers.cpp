题意：
二叉树中每条路径都表示一个整数，求所有路径上值的总和。
思路：
1.除了第一个根结点以外，只要有新的结点值，更新结点值为其原值+根结点的值*10
2.输出的总和等于所有叶子结点的和，即当一个结点没有左右子树的时候total相加。
注意：
1.可能会有当和很大的时候的follow up,需要更换为long long类型。
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
    int sumNumbers(TreeNode* root) {
        int total = 0;
        helper(root, total);
        return total;
    }
    
    void helper(TreeNode* root,int &total){
        if(!root) return;
        if(root -> left == NULL && root -> right == NULL) total += root -> val;
        if(root -> left) root -> left -> val = root -> left -> val + 10*root -> val;
        if(root -> right) root -> right -> val = root -> right -> val + 10*root -> val;
        helper(root -> left, total);
        helper(root -> right, total);
    }
};
还有一个思路是：
每遇到一个结点，就把所有原来的数字扩大10倍以后再相加。
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
    int sumNumbers(TreeNode* root) {
        return helper(root, 0);
    }
    
    int helper(TreeNode* root,int total){
        if(!root) return 0;
        total = total * 10 + root -> val;
        if(! root -> left && ! root -> right) return total;
        return helper(root -> left, total) + helper(root -> right, total);
    }
};