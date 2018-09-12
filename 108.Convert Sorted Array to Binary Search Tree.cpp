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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root;
        root = CreateTree(root, nums, 0, nums.size()-1);
        return root;
    }
    TreeNode* CreateTree(TreeNode* root, vector<int>& nums, int start, int end){
        if(start > end){
            return NULL;
        }
        root = new TreeNode(0);
        root -> val = nums[(start+end+1)/2];
        root -> left = CreateTree(root ->left, nums, start, (start+end+1)/2-1);
        root -> right = CreateTree(root ->right, nums, (start+end+1)/2+1, end);
        return root；
        
    }
};

/*
思路：
1.因为要求形成二叉平衡树，即每个结点的左子树和右子树的高度差的绝对值小于等于1，因此需要首先找到跟结点的位置，即vector中的中位数
2.再分别找到左子树的根结点和右子树的根结点，从而形成递归
3.需要用到的变量有，root，原vector,起点值和结尾值

注意：
1.要注意root与其左右子结点的连接
root = new TreeNode(0);//首先需要创建跟结点结构，再赋新值
所有的操作应该都从根结点开始，root -> val, root ->left, root -> right
2.start和end如何计数（到哪一位）可自定，能表示大小关系即可
3.注意需要有(start+end+1)/2-1)和(start+end+1)/2+1中+1，-1的操作，以此当start大于end的时候返回NULL
*/