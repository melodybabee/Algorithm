题意：
二叉树之字型层序遍历
方法一：递归
思路：同102的递归思路，在输出前加入一层循环，如果是奇数奇数行调用reverse()方法反转即可
注意：reverse()方法直接调用，比如反转A，写作reverse(A.begin(),A.end());
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        bfs(root,0,ret);
        for(int i =0; i< ret.size();++i){
            if(i%2==1){
                reverse(ret[i].begin(),ret[i].end());
            }
        }
        return ret;
    }
    void bfs(TreeNode* root, int level, vector<vector<int>>&ret){
        if(!root) return;
        if(ret.size() == level) ret.push_back({});
        ret[level].push_back(root -> val);
        bfs(root->left,level+1,ret);
        bfs(root->right,level+1,ret);
    }
};
方法2:用两个栈进行遍历
思路：
1.因为要求对树进行隔行同序输出，其他逆序输出，所以需要在push的过程中建立两个栈，分别交叉插入
当目前所在的栈已经为空的时候push到大的vector中
注意：
因为if(!out.empty())ret.push_back(out);这一步是在while循环外侧，因此如果到s1已经结束但是s2的out为空的话，还会输出一个空数组，因此需要在每次输入之前判断一下
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<int>out;
        vector<vector<int>>ret;
        if(!root) return ret;
        stack<TreeNode*> s1;
        stack<TreeNode*> s2;
        s1.push(root);
        while(!s1.empty() || !s2.empty()){
            while(!s1.empty()){
                TreeNode*p = s1.top();
                s1.pop();
                out.push_back(p->val);
                if(p->left)s2.push(p->left);
                if(p->right)s2.push(p->right);
            }
            if(!out.empty())ret.push_back(out);
            out.clear();
            while(!s2.empty()){
                TreeNode*p = s2.top();
                s2.pop();
                out.push_back(p->val);
                if(p->right)s1.push(p->right);
                if(p->left)s1.push(p->left);
            }
            if(!out.empty())ret.push_back(out);
            out.clear();
        }
        return ret;
    }
};