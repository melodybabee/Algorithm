题意：
树的前序遍历。
方法一：递归
注意在没有根结点的时候直接返回即可，不要返回空，这样会形成空结点。
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        preorder(root,ret);
        return ret;
    }
    void preorder(TreeNode* root,vector<int>&ret){
        if(!root) return;
        else{
            ret.push_back(root->val);
            preorder(root->left,ret);
            preorder(root->right,ret);
        }
    }
};
方法2：遍历
思路：
二叉树的前序遍历用stack来存储根结点，进入循环后设置树结点便于读取结点的值输出。
根据栈后进先出的性质，再依次放入右子树和左子树。
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
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*>st;
        vector<int>vec;
        if(!root) return vec;
        st.push(root);
        while(!st.empty()){
            TreeNode *t = st.top();
            st.pop();
            vec.push_back(t->val);
            if(t->right) st.push(t->right);
            if(t->left) st.push(t->left);
        }
        return vec;
    }
};
方法3:模版【默写】
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>ret;
        stack<TreeNode*> st;
        TreeNode *p= root;
        while(p || !st.empty()){
            if(p){
                st.push(p);
                ret.push_back(p->val);
                p = p -> left;
            }else{
                TreeNode *q = st.top();
                st.pop();
                p = q->right;
            }
        }
        return ret;
    }
};