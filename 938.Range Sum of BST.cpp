题意：
找出给定范围内二叉搜索树中存在的结点和。
思路：
1.二叉搜索树注意用到其性质，从最左结点到最右结点中序遍历是递增的。
那么从根结点开始，如果根结点在给定的范围内，加上根结点，对左右子树依次递归。
如果根结点不在给定的范围内，那么以左／右子树为根结点再次判断是否在给定范围内，进行递归即可。
2.递归的边界条件是如果不存在根结点说明到了最后一层，返回0；
如果根结点的值小于左／大于右，那么重新递归；
如果在范围内，那么把根结点的值求和即可。
最后返回和。
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
    int rangeSumBST(TreeNode* root, int L, int R) {
        if(!root) return 0;
        int total = 0;
        return findSum(root,L,R, total);
    }
    
    int findSum(TreeNode* root, int L, int R, int &total){
        if(!root) return 0;
        if(root -> val < L) return findSum(root -> right,L,R,total);
        if(root -> val > R) return findSum(root -> left, L,R,total);
        total += root -> val;
        findSum(root -> left,L,root -> val,total);
        findSum(root -> right, root -> val, R,total);
        return total;
     }
};