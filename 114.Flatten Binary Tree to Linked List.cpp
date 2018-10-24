题意：
把一个二叉树变成只有右子树的链表形式
方法一：递归
思路：
1.找到左子树的左结点，直到没有左子树后，递归右结点，设置一个中间变量记录右子树，把左子树移动到根结点的右侧
再找到最右结点连接之前保存下来的右子树
2.依次递归
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
    void flatten(TreeNode* root) {
        if(!root) return;
        if(root -> left) flatten(root -> left);
        if(root -> right) flatten(root -> right);
        TreeNode *temp = root -> right;
        root -> right = root -> left;
        root -> left = NULL;
        while(root -> right) root = root -> right;
        root -> right = temp;
    }
};
方法二：遍历，不用栈
思路：
1.首先判断根结点的左子树是否存在，存在的话把左子树的最右结点连接上根结点的右子树
2.使根结点的右子树等于左子树，左子树为空
3.再依次循环右子树，如果仍有左结点，再次调用此方法，直到没有右结点为空为止
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* cur = root;
        while(cur){
            if(cur->left){
                TreeNode*p = cur -> left;
                while(p->right) p = p -> right;
                p->right = cur -> right;
                cur ->right = cur->left;
                cur -> left = NULL;
            }
            cur = cur -> right;
        }
    }
};
方法三：遍历，用栈
思路：
1.和不用栈的思路类似，只不过这个方法中只要当前结点有右结点，就入栈，然后判断它是否有左结点，有左结点交换
2.如果没有左结点，继续判断是否有右结点，如果有push到栈中，直到没有右结点即循环结束
class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        stack<TreeNode*>st;
        st.push(root);
        while(!st.empty()){
            TreeNode* pre = st.top();
            st.pop();
            if(pre -> left){
                TreeNode*p = pre -> left;
                while(p->right) p = p ->right;
                p -> right = pre -> right;
                pre -> right = pre -> left;
                pre -> left = NULL;
            }
            if(pre->right) st.push(pre->right);
        }
    }
};
