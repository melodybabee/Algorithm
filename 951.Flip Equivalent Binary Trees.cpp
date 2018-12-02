题意：
如果两个树通过旋转其中某些结点的左右子树可以得到相同的树，那么两个树被判定为相等的。判断两个树能否相等。
思路：
1.从根结点开始，如果都不存在根结点，true;如果一个存在根结点一个不存在根结点，false;
2.如果两个树的根结点的值不等，那么返回false;
3.分别递归两个树的左子树和右子树，如果都为true，返回true;
4.再分别递归两个树的左子树和右子树，如果都为true,返回true.
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
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;
        if(root1->val != root2-> val) return false;
        if(flipEquiv(root1 -> left,root2->left) && flipEquiv(root1 -> right, root2 -> right)) return true;
        if(flipEquiv(root1 -> right,root2->left) && flipEquiv(root1 -> left, root2 -> right)) return true;
        return false;
    }
};