题意：
树的后序遍历。
方法一：递归：
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        helper(root,ret);
        return ret;
    }
    
    void helper(TreeNode *root, vector<int>&ret){
        if(!root) return;
        helper(root -> left, ret);
        helper(root -> right,ret);
        ret.push_back(root -> val);
    }
};
方法二：遍历：
注意
1.后序遍历的顺序是左->右->中。
2.需要一个last来记录已经被输出的点。因为后序遍历输出左结点之后，会返回根结点判断有没有右子树，如果有那么cur会开始遍历右子树。
栈中会依次输入右子树。
但是当右子树输入完成之后，还会回到根结点，那么此次不应该再进入右子树，因此需要把连接根结点的右结点标记下来，如果右子树等于它便不再输入右子树。
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*>st;
        TreeNode *cur = root;
        TreeNode *last = NULL;
        while(!st.empty() || cur){
            if(cur){
                st.push(cur);
                cur = cur-> left;
            }else{
                TreeNode *temp = st.top();
                if(temp -> right && temp -> right != last){
                    cur = temp -> right;
                }else{
                    ret.push_back(temp -> val);
                    last = temp;
                    st.pop();
                }
            }
        }
        return ret;
    }
};