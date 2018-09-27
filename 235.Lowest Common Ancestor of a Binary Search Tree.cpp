补充：
1.LCA：lowest Common Ancestor,最近公共祖先，每一个节点指向父节点，因此从下往上直到根节点，找到x和y的第一个相交点，即为最近公共祖先。
可以分为四种四种情况：
（1）两个结点都在左子树上
（2）两个结点都在右子树上
（3）一个结点在左子树，一个结点在右子树
（4）当前一个值为另一个的父结点
2.本题是BST，二叉搜索树，满足二叉搜索树的性质，抓住递归的本质即可
（1）若左子树不空，则左子树上所有结点的值均小于或等于它的根结点的值；
（2）若右子树不空，则右子树上所有结点的值均大于或等于它的根结点的值；
（3）左、右子树也分别为二叉排序树；
由此可以判断p,q两点的位置。
思路：
1.因为p,q是二叉搜索树上的两个结点，找到其共同的父结点，要不都在左子树，要不都在右子树，或者是一左一右，根结点为父结点
2.因此用p,q的值与根结点的值进行比较即可，不断递归，最后返回根结点即可
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p->val < root->val && q->val < root ->val)
            return lowestCommonAncestor(root->left,p,q);
        if(p->val > root->val && q->val > root ->val)
            return lowestCommonAncestor(root->right,p,q);
        else
            return root;
    }
};