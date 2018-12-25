题意：判断两棵树的叶子结点是否是完全相同的
方法一：递归
思路：
1.分别对两颗树进行遍历，当左右子树都不存在的时候把叶子结点输出到新的数组中
2.最后判断两个输出的数组是否相同
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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> vec1;
        vector<int> vec2;
        helper(root1, vec1);
        helper(root2, vec2);
        return vec1 == vec2;
    }
    
    void helper(TreeNode*root, vector<int>&vec){
        if(!root) return;
        if(!root -> left && !root -> right) vec.push_back(root->val);
        helper(root -> left, vec);
        helper(root -> right, vec);
        return;
    }
}
优化：也可以不用数组来记录返回的叶子结点值，直接用一个string来记录