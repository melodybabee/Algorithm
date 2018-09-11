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
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return max(maxDepth(root -> left),maxDepth(root -> right)) +1;
        
    }
};

/*
思路：
1.想要找到树的最大深度，即找到左右子树的最大深度取最大即可，当根不存在的时候（即到叶子结点之后，return 0）
2.通过divide and conquer的思路可以想到用递归的方法
3.leetcode中根结点的深度为1
*/