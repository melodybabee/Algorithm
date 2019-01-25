题意：找到二叉搜索树中两个结点之差最小的值
思路：
1.因为在BST中，最小的差值一定出现在两个相邻的结点之间，因此中序遍历二叉树形成一个数组
2.在数组中找两两之差的最小值。
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
    int getMinimumDifference(TreeNode* root) {
        vector<int>vec;
        helper(root,vec);
        int ret = INT_MAX;
        for(int i = 0; i < vec.size()-1; ++i){
            ret = min(vec[i+1]-vec[i],ret);
        }
        return ret;
    }
    
    void helper(TreeNode* root, vector<int>&vec){
        if(!root) return;
        helper(root->left,vec);
        vec.push_back(root->val);
        helper(root->right,vec);
    }
};
优化：
1.利用一个pre记录下遍历到的每个结点，初始值为-1.中序遍历依次进行差值比较，取小。
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
    int getMinimumDifference(TreeNode* root) {
        int ret = INT_MAX;
        int pre = -1;
        helper(root,ret,pre);
        return ret;
    }
    
    void helper(TreeNode* root, int &ret, int &pre){
        if(!root) return;
        helper(root->left,ret,pre);
        if(pre != -1) ret = min(ret,root->val-pre);
        pre = root -> val;
        helper(root->right,ret,pre);
    }
};