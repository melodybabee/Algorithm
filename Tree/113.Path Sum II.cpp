题意：
找到所有和等于目标值的路径并输出。（112变形）
方法：回溯
思路：
1.二叉树的遍历可以想到DFS回溯，因此是典型的回溯+递归
2.但是需要注意每次进入dfs方法时，需要先把根结点的值放到vector中，再进行判断，不然会少最后一个结点
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<int> temp;
        vector<vector<int>> ret;
        dfs(root,sum,temp,ret);
        return ret;
    }
    void dfs(TreeNode* root,int sum,vector<int>&temp,vector<vector<int>>&ret){
        if(!root) return;
        temp.push_back(root -> val);
        if(!root -> left && !root -> right && sum == root->val) {
            ret.push_back(temp);
        }
        int newsum = sum - root -> val;
        dfs(root->left,newsum,temp,ret);
        dfs(root->right,newsum,temp,ret);
        temp.pop_back();
        
    }
};
方法：遍历
思路：
1.利用树的中序遍历，首先找到左结点，进行判断
2.利用一个vector来记录遍历到过的结点，如果到了叶子结点和等于目标值，push_back
如果不等，记录下当前位置，cur结点返回到上一层，找是否有右子树
3.始终用pre记录下cur的当前位置，便于cur返回上一层
pre用于区分cur是第一次进入右子树，还是从右子树一步一步返回上去的
注意：vector获得尾部元素可以用vector.back();
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<TreeNode*> temp;
        vector<vector<int>> ret;
        TreeNode* cur = root;
        TreeNode* pre = NULL;
        int val = 0;
        while(cur || !temp.empty()){
            while(cur){
                temp.push_back(cur);
                val += cur->val;
                cur = cur->left;
            }
            cur = temp.back();
            if(!cur -> left && !cur -> right && val == sum){
                vector<int> s;
                for(auto &i : temp) s.push_back(i->val);
                ret.push_back(s);
            }

            if(cur -> right && cur -> right != pre) cur = cur -> right;
            else{//注意这个else是跟着上面这个if的，也就是说，第一个if满足条件进入，不满足条件进入第二个if，如果第二个if条件不满足会进入else，和第一个if是否满足条件无关
                pre = cur;
                val -= cur -> val;
                temp.pop_back();
                cur = NULL;
            }
        }
        return ret;
    }
};

12.2复习：
递归：易错点在于进入递归之后什么时候在temp数组中push当前根结点的值。先push再判断。
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> ret;
        vector<int>temp;
        helper(root,sum,ret,temp);
        return ret;
    }
    
    void helper(TreeNode* root, int sum,vector<vector<int>>&ret,vector<int>&temp){
        if(!root) return;
        temp.push_back(root->val);
        if(!root -> left && !root -> right && root -> val == sum) {
            ret.push_back(temp);
        }
        helper(root -> left, sum - root->val, ret,temp);
        helper(root -> right, sum - root->val, ret,temp);
        temp.pop_back();
    }
};

遍历：
树的前序遍历，注意pre的用法，用来记录cur的右结点为了不使cur反复进入右结点。
debug一定要一行一行仔细看，不要借助编译器，有的笔误编译器也看不出来==
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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<int>temp;
        vector<vector<int>> ret;
        stack<TreeNode*> st;
        TreeNode *cur = root;
        TreeNode *pre = NULL;
        int total = 0;
        while(!st.empty() || cur != NULL){
            while(cur){
                st.push(cur);
                temp.push_back(cur->val);
                total += cur -> val;
                cur = cur -> left;
            }
            cur = st.top();
            if(!cur -> left && ! cur-> right && total == sum) {
                ret.push_back(temp);
                pre = cur;
                st.pop();
                total -= cur -> val;
                temp.pop_back();
                cur = NULL;
                continue;
                
            } 
            if(cur -> right  && pre != cur -> right){
                cur = cur -> right;
            }
            else{
                pre = cur;
                st.pop();
                temp.pop_back();
                total -= cur -> val;
                cur = NULL;
            }
        }
        return ret;
    }
};