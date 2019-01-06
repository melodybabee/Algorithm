voyage 航线
题意：
判断一棵树能否通过交换左右子树变成规定的前序遍历顺序。
思路：
1.首先需要一个数组来记录需要转换的结点，一个指针记录指定数组中的位置坐标
2.进入DFS遍历，如果不存在根结点，那么返回true；如果根结点的值不等于当前位置的数组中的值，返回false
3.判断左右结点是否存在，如果左结点存在且等于当前数组中的值，那么对左右子树调用递归
如果右结点存在且等于当前数组中的值，如果左结点存在，则说明需要交换，同时对当前结点进行先右子树再左子树调用递归
4.如果都不满足上述情况，如果已经到叶子结点，那么返回true，如果还有左子树或者右子树，那么返回false。因此需要返回!root->left && !root -> right
5.在主函数中，如果返回了true,那么直接输出数组。如果返回的是false,那么返回-1。
注意：
因为数组中的坐标也需要不断的向前移动，因此在比较过程中需要用到i++，即先比较，不管是否满足条件都会将指针移动到下一位的位置
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
    int i = 0;
    vector<int>ret;
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        if(helper(root,voyage)) return ret;
        ret.clear();
        return {-1};
    }
    
    bool helper(TreeNode* root, vector<int>& voyage){
        if(!root) return true;
        if(root -> val != voyage[i++]) return false;
        if(root -> left && root -> left -> val == voyage[i]){
            return helper(root->left,voyage) && helper(root->right,voyage);
        }else if(root -> right && root -> right -> val == voyage[i]){
            if(root->left)ret.push_back(root->val);
            return helper(root -> right, voyage) && helper(root->left, voyage);
        }
        
        return !root->left && !root -> right;
    }
};