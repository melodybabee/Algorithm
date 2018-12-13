题意：
找到二叉树中的最大路径。
思路：
1.题目中的意思是找到从任意结点到任意结点的最大路径，那么有3种情况：
前两种情况可以归纳为：root->leaf path中的一段
(1)从根结点出发到其左子树路径上叶子结点中的最大值
(2)从根结点出发到其右子树路径上叶子结点中的最大值
两个节点之间经过它们lowest common ancestor (LCA)的path
(3)以根结点为过度，左子树某个结点开始+根结点+右子树某个结点结束的路径较大值
2.往常自上至下的递归方法不适用因为对于找LCA路径的情况，它的path sum同时取决于LCA左右sub path的最大值。而这样的path sum是无法通过top-down传递来获取的。
3.那么就要采用自下至上的方法，找到两种情况下的较大值：
(1)从某一点出发向leaf方向的第一类path中最大的path sum
(2)以某一点为LCA的第二类path中的最大path sum
4.分别从左右两边找到左右子路径中的较大值，用ret记录下过程中遇到的较大值，有可能是左右子树或者是左右子树+根结点的值。
返回的结果是左右子树中较大的一侧+根结点的值，为了判断包括LCA的路径是否是较大的。
5.因为根结点本身也可以作为一个结果，因此左右子树中如果有负值需要舍弃，负值越加越小。
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
    int maxPathSum(TreeNode* root) {
        int ret = INT_MIN;
        helper(root,ret);
        return ret;
    }
    
    int helper(TreeNode*root,int &ret){
        if(!root) return 0;
        int left = max(helper(root -> left,ret),0);
        int right = max(helper(root -> right,ret),0);
        ret = max(ret,left+right+root->val);
        return max(left,right)+root->val;
    }
};

12.11复习：
注意：
1.核心的递归思想是分别计算左右子树中的较大值，最后返回的结果应该是左右子树+根结点中的较大值和原结果中的较大值。
2.但是每次递归返回的是左右子树的较大值+根结点。如果返回值为负数那么直接取0.
3.即返回值和得到的结果不是同一个值。
4.递归调用的是int类型
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
    int maxPathSum(TreeNode* root) {
        int ret = INT_MIN;
        helper(root,ret);
        return ret;
    }
    
    int helper(TreeNode *root, int &ret){
        if(!root) return 0;
        int left = max(helper(root -> left,ret),0);
        int right = max(helper(root -> right,ret),0);
        ret = max(ret,left + right + root ->val);
        return max(left,right)+ root -> val;
    }
};