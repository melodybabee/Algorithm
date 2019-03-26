遍历做法：
1.因为需要输出二叉树的所有路径，因此需要依次遍历树的每一个结点，同时记录下遍历过的路径
2.设立两个栈，一个用于记录遍历到的结点，一个用于记录需要返回的string,注意因为结点的值为int类型，因此转换为string的时候需要用到to_string
3.先把根结点放入栈中，每次栈不为空的时候，分别取出两个栈的顶部元素，如果顶部元素的左右都为空，说明已经到叶子结点，则将string栈中过的顶部元素push到vector中
4.如果左右有一边或都不为空，分别放入stack中，注意string的stack中需要放的是所有遍历过的路径，最后才能直接push到vector中，用现有的值加上新的值
5.当放结点的stack不是空时，返回vector
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ret;
        if(root == NULL) return ret;
        stack<TreeNode*> st;
        stack<string> path;
        st.push(root);
        path.push(to_string(root->val));
        
        while(!st.empty()){
            TreeNode *p = st.top();
            st.pop();
            string q = path.top();
            path.pop();
            
            if(p->left == NULL && p ->right == NULL){
                ret.push_back(q);
                continue;
            }
            if(p->right != NULL){
                st.push(p->right);
                path.push(q + "->" + to_string(p->right->val));
            }
            if(p->left != NULL){
                st.push(p->left);
                path.push(q + "->" + to_string(p->left->val));
            }
            
        }
        return ret;
    }
};

递归做法：
1.整体思路和遍历相同，不停的找DFS树的叶结点，没有左右结点的时候，一条完整的路径已经形成
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string>ret;
        if(root == NULL) return ret;
        dfs(root, to_string(root->val), ret);
        return ret;
    } 
    
    void dfs(TreeNode* root, string path, vector<string>&ret){
        if(root -> left == NULL && root -> right ==NULL){
            ret.push_back(path);
        }
        if(root -> left != NULL){
            dfs(root->left,path+"->"+to_string(root->left->val),ret);
        }
        if(root -> right != NULL){
            dfs(root->right,path+"->"+to_string(root->right->val),ret);
        }
    }
};

12.12复习：
递归做法：
注意：
1.注意需要返回的是string,所以需要对结点值进行转化，to_string(root->val)
2.只要根结点存在那么先加入根结点
3.因此在递归时需要判断如果根左根右都不存在的话那么应该push进去当前路径了
在递归调用某一边之前都需要判断其右或者其左是否存在。
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string>ret;
        if(!root) return ret;
        helper(root,ret,to_string(root->val));
        return ret;
    }
    
    void helper(TreeNode* root,vector<string>&ret,string str){
        if(!root -> left && !root -> right) ret.push_back(str);
        if(root -> left)
        helper(root -> left,ret,str + "->"+to_string(root ->left -> val));
        if(root -> right)
        helper(root -> right,ret,str + "->"+to_string(root ->right -> val));
    }
};

3.25复习：
注意：
1.如果最开始是空的字符串的话，那么首先需要加上值，再加上->
2.再开始进入递归，递归的终止条件是如果到了叶子结点，那么加上最后一个值之后直接清空
3.因为递归的终止条件是判断其左右结点是否存在，不是判断该结点是否存在。所以在进入递归之前需要判断左右结点是否存在。
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ret;
        if(!root) return ret;
        string str = "";
        helper(root,ret,str);
        return ret;
    }
     void helper(TreeNode* root, vector<string> &ret, string str){
         if(!root->left && ! root->right){
             str += to_string(root->val);
             ret.push_back(str);
             str = "";
             return;
         }
         str += to_string(root->val);
         str += "->";
         if(root->left)helper(root->left, ret, str);
         if(root->right)helper(root->right, ret, str);
     }
};