题意：找到树中结点值相等的最长路径
思路：
1.因为要求出最长的子路径，那么从根结点开始进入递归，分别设置新的变量对左右结点进行递归
2.对求出的左右结点变量进行更新，如果左存在而且跟等于左边，那么左边+1，如果不同左边就为0，右侧同理、
3.结果值为当前值和左边+右边的和的较大值
而返回值等于左右两边中较大的一个值
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
    int longestUnivaluePath(TreeNode* root) {
        int ret = 0;
        helper(root,ret);
        return ret;
    }
    int helper(TreeNode* root,int &ret){
        if(!root) return 0;
        int left = helper(root->left,ret);
        int right = helper(root->right,ret);
        left = (root->left && root-> val == root ->left ->val) ? left+1:0;
        right = (root->right && root-> val == root ->right->val) ? right+1:0;
        ret = max(ret,left+right);
        return max(left,right);
    }
};