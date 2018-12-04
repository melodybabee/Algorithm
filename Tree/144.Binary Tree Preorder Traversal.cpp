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

12.3复习：
递归：
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
        helper(root, ret);
        return ret;
    }
    
    void helper(TreeNode* root, vector<int>&ret){
        if(!root) return;
        ret.push_back(root->val);
        helper(root -> left, ret);
        helper(root -> right,ret);
    }
};

遍历：
注意：
前序遍历是如果根结点存在，输出根结点，根结点向左。根结点不存在的话表明已经到最左，需要出栈向右查找。
中序遍历是只要左结点存在，就一直向左直到没有向左的结点，输出向左的结点，根结点出栈输出，找右结点入栈。
相同：
进入遍历的条件都是栈不为空或者遍历的指针cur存在。
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
        stack<TreeNode*>st;
        TreeNode *p = root;
        while(!st.empty() || p){
            if(p){
            ret.push_back(p->val);
            st.push(p);
            p = p -> left;
            }else{
                p = st.top();
                st.pop();
                p = p -> right;
            }
        }
        return ret;
    }
};

线索二叉树：
同样需要pre来记录遍历到右结点或者没有右结点之后需要连接的下一位。
注意只要不存在右结点那么首先把cue输出到结果值里面。
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
        TreeNode *cur = root;
        TreeNode *pre = NULL;
        while(cur){
            if(cur -> left){
                pre = cur -> left;
                while(pre -> right && pre -> right != cur) pre = pre -> right;
                if(!pre -> right){
                    ret.push_back(cur->val);
                    pre -> right = cur;
                    cur = cur -> left;
                }else{
                    pre -> right = NULL;
                    cur = cur -> right;
                }
            }else{
                ret.push_back(cur -> val);
                cur = cur ->right;
            }
        }
        return ret;
    }
};