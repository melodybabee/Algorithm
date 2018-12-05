题意：
输出二叉树的右侧视角。
方法一：DFS递归
思路：
1.从根结点开始递归，只要有右子树那么先递归右子树。
2.注意会存在左子树比右子树短的情况，那么就需要增加一个层数变量。
当输出数组中的个数小于层数的时候，就在结果数组中输入第一个遍历到的元素，先右后左。
3.leetcode中所有树的层数从1开始。
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int>ret;
        helper(root,ret,1);
        return ret;
    }
    
    void helper(TreeNode* root, vector<int>&ret,int level){
        if(!root) return;
        if(ret.size() < level)ret.push_back(root->val);
        helper(root -> right, ret,level+1);
        helper(root -> left, ret,level+1);
    }
};

方法2:BFS遍历
思路：
1.层序遍历，每次输出栈顶元素的值，记录下当前栈中的元素个数
2.开始进入for循环，目的是把栈中元素的下一层元素全部入栈，先右后左，这样每次进入while循环后第一个元素就是想要的元素。
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
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*>q;
        vector<int> vec;
        if(!root) return vec;
        q.push(root);
        while(!q.empty()){
            vec.push_back(q.front() -> val);
            int size = q.size();
            for(int i = 0; i < size;++i){
                TreeNode *temp = q.front();
                q.pop();
                if(temp -> right)q.push(temp -> right);
                if(temp -> left) q.push(temp -> left);
            }
        }
        return vec;
    }
};