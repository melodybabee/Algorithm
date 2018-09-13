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
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        if(!root -> left) return minDepth(root -> right)+1;
        if(!root -> right) return minDepth(root -> left)+1;
        
        return min(minDepth(root -> left), minDepth(root -> right)) +1;
        
        
    }
};

/*
思路：
1.与找最大深度一样，从根结点开始不断递归，比较返回的左右子树高度，取小
注意：
1.应为根结点的高度默认为1，因此需要+1
2.与找最大高度不同，当左右其中一个为空的时候，不能返回0，需要返回不为空的子树，因此需要单独考虑这个情况
*/