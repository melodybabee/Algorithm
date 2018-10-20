题意：树的前序遍历
方法1:递归
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ret;
        inorder(root, ret);
        return ret;
    }
    void inorder(TreeNode* root,vector<int>&ret){
        if(!root) return;
        if(root->left) inorder(root -> left,ret);
        ret.push_back(root->val);
        if(root->right) inorder(root -> right,ret);
    }
};
方法二：遍历
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
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode *p = root;
        vector<int> ret;
        while(!st.empty()||p){
            while(p){
                st.push(p);
                p = p->left;
            }
            p = st.top();
            st.pop();
            ret.push_back(p->val);
            p = p->right;
        }
        return ret;
    }
};
方法三：线索二叉树。threaded binary tree
不用栈不用递归，Morris Traversal
思路：
总体思路：在中序遍历中，将所有为空的右子结点指向中序遍历的下一个结点
1.初始化指针cur指向root
2. 当cur不为空时
如果cur没有左子结点：
a) 打印出cur的值
b) 将cur指针指向其右子节点
如果cur有左子结点：
将pre指针指向cur的左子树中的最右子节点，去寻找最右子结点
3.若pre不存在右子节点，即右子结点为空的时候，将其右子节点指回cur，cur指向其左子节点
若pre有右子节点但是还是跳出while循环，说明pre的右子结点等于cur,之前已经遍历到这一位把它连接到了遍历它之后的下一个结点的位置
那么，将pre的右子节点置空，输出cur的值，将cur指针指向其右子节点

注意：这样一来，所有没有右子结点的值都会有右指针，连接下一位应该输出的值，所以cur一直找他的右子结点就可以了。
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ret;
        TreeNode*pre;
        TreeNode *cur = root;
        if(!root) return ret;
        while(cur){
            if(!cur->left){
                ret.push_back(cur->val);
                cur = cur -> right;
            }else{
                pre = cur->left;
                while(pre ->right && pre -> right != cur) pre = pre -> right;
                if(!pre->right){
                    pre -> right = cur;
                    cur = cur ->left;
                }else{
                    pre -> right = NULL;
                    ret.push_back(cur->val);
                    cur = cur -> right;
                }
            }
        }
        return ret;
    }
};