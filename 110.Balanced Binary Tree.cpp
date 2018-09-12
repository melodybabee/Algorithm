/**
 * Definition a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        if(abs(findMax(root -> left)-findMax(root -> right)) > 1)
           return false;
        return isBalanced(root -> left) && isBalanced(root -> right);
    }
    
    int findMax(TreeNode *root){
        if(!root) return 0;
        int l = findMax(root -> left) +1;
        int r = findMax(root -> right) +1;
        return max(l,r);
        }
};
//T(n) = O(nlogn),S(n) = O(n)
/*思路：
1.判断平衡二叉树的标准是所有结点左右子树的高度差的绝对值大于等于1
2.因此可以自下而上利用递归的方法进行，从根结点开始分别找到左子树和右子树的最大高度进行判断
3.再以此类推进行每个结点的比较

注意：
1.找子树高度的时候需要用到递归，同时判断每个结点会再用到递归，两次递归（时间复杂度较高）
2.解释为什么时间复杂度是nlogn
(1)首先isbalanced循环中， 需要走完所有结点，因此是n
(2)在findMax的遍历中，一共需要走树的层数h,h = logn,n为结点个数
*深度为h的二叉树中，第i层上最多有2的i-1次幂个结点，一共最多有（2的h次幂-1）个结点，因此n的结点时，2的h-1次幂-1< n <= 2的h次幂-1
同时进行log运算，因此h=log2n(向下取整）+1， 约为log2n
*／
