题意：把二叉搜索树转换为Greater Tree
思路：
1.首先中序遍历计算出二叉树的总和
2.再次中序遍历对每一个结点进行处理，和依次减去每个结点的值，再赋值到新的结点上
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
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        helper(root,sum);
        getresult(root,sum);
        return root;
    }
    
    void helper(TreeNode*root, int &sum){
        if(!root) return;
        helper(root->left, sum);
        sum += root->val;
        helper(root->right,sum);
    }
    
    void getresult(TreeNode*root, int &sum){
        if(!root) return;
        getresult(root->left, sum);
        int temp = root->val;
        root->val = sum;
        sum -= temp;
        getresult(root->right,sum);
    }
    
};

优化：也可以直接从右侧开始递归求和