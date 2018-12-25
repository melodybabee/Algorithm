trim 修剪
题意：在指定范围内修剪二叉搜索树
方法一：递归
思路：
1.首先判断如果根结点不存在直接返回空
2.如果根结点的值不在左->右的范围内，那么直接对在范围内的一侧调用递归，注意此处要直接返回，因为根结点已经发生变化
3.如果根结点在中间或者根结点正好等于左右边界值的其中之一，那么分别更新左右子树，注意连接。
重新对左右子树调用递归即可，回直接舍弃掉不符合条件的结点。
4.最后返回根结点。
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
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if(!root) return NULL;
        if(root -> val > R) return trimBST(root -> left, L, R);
        if(root -> val < L) return trimBST(root -> right, L, R);
        root -> left = trimBST(root -> left, L ,R);
        root -> right = trimBST(root -> right, L, R);
        return root;
    }
};

方法二：遍历
思路：
1.一般树的问题都可以用递归来解决，如果用遍历的方法写，首先考虑while写法
2.首先确定好根结点的值，即根结点应该在左右范围内
3.再依次判断左右子树，如果超出了左侧或者右侧的范围，那么直接用当前结点连接它的下一个结点。
利用BST性质，如果左侧结点不满足，直接移动到其右侧，为空的时候结束。如果右侧不满足，直接移动到下一位的左侧。
4.注意同样要设置一个cur指针便于操作，最后返回根结点。
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
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if(!root) return NULL;
        while(root -> val < L || root -> val > R){
            root = (root -> val < L) ? root -> right : root -> left;
        }
        TreeNode *cur  = root;
        while(cur){
            while(cur -> left && cur -> left -> val < L){
                cur -> left = cur -> left -> right;
            }
            cur = cur -> left;    
        }
        cur = root;
        while(cur){
            while(cur -> right && cur -> right -> val > R){
                cur -> right = cur -> right -> left;
            }
            cur = cur ->right;
        }
        return root;
    }
};