题意：
二叉树的层序遍历
方法一：递归
思路：
1.因为是层序遍历，因此需要记录下递归的层数
2.如果返回的vector的大小等于层数，那么首先push进去一个{},再把当前的根的值push进去，再去遍历右子树
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        bfs(root,0,ret);
        return ret;
    }
    void bfs(TreeNode* root,int level,vector<vector<int>>&ret){
        if(!root)return;
        if(ret.size()==level) ret.push_back({});
        ret[level].push_back(root->val);
        bfs(root->left,level+1,ret);
        bfs(root->right,level+1,ret);
    }
};
方法2:用queue遍历
思路：
1.首先将根结点入栈，特点是每一层的结点个数正好为队列的长度，因此调用头结点，在个数小于栈的长度的条件下，以此输出值
2.出栈，同时如果有新的左子结点或者右子结点的话再入栈，循环结束把小的vector的结果push到大的vector中，直到栈空
注意：
在树的BFS遍历的时候用队列，树的DFS中序遍历时用栈
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*>q;
        vector<vector<int>> ret;
        if(root == NULL) return ret;
        q.push(root);
        while(!q.empty()){
            vector<int> v;
            int level = q.size();
            for(int i = 0; i < level;++i){
                TreeNode* p = q.front();
                q.pop();
                v.push_back(p -> val);
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
            ret.push_back(v);
        }
        return ret;
    }
};