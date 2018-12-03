题意：
找到二叉树中所有和等于目标值的路径（包括子路径）
方法1.完全递归
思路：
1.题目中是要求找到以所有等于目标值的子路径，那么首先每个结点都能成为根，因此第一层递归的是根结点的和+左子树作为根的树+右子树作为根的树（以结点划分跟）
2.第二层递归再求所有以当前跟为根结点的路径的和，是否等于目标值。
用pre记录当前的和，新的和=当前和+新的结点值。如果val == sum为真，那么值为1，表示个数；如果val == sum为假，那么值为0
再调用左子结点和右子结点
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        if(!root) return 0;
        return sumUp(root,0,sum) + pathSum(root -> left, sum) + pathSum(root -> right,sum);
    }
    
    int sumUp(TreeNode* root, int pre, int &sum){
        if(!root) return 0;
        int val = pre + root-> val;
        return (val == sum) + sumUp(root -> left, val,sum) + sumUp(root -> right, val,sum);
    }
};
方法二：回溯
思路：
1.从根结点开始回溯，在helper函数中用一个for循环计算从根结点到该点之间所有的子路径是否满足等于目标值。
2.注意在找子结点的时候需要保留最后一个结点，不然在target==0的时候会出错，而每个结点的值会在以它本身为根的时候被循环到。
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        int ret = 0;
        vector<TreeNode*> node;
        helper(root, node,0, sum,ret);
        return ret;
    }
    void helper(TreeNode* root,vector<TreeNode*>&node, int cur, int sum,int &ret){
        if(!root) return;
        cur += root->val;
        node.push_back(root);
        if(cur == sum) ++ret;
        int temp = cur;
        for(int i = 0; i< node.size()-1;++i){
            temp -= node[i]->val;
            if(temp == sum) ++ret;
        }
        helper(root->left, node,cur, sum,ret);
        helper(root->right, node,cur, sum,ret);
        node.pop_back();
    }
};

12.2复习
遍历：
核心思路是从根结点依次相加递归，把从根结点到当前结点的所有结点存到一个vector中，每遍历到一个新的结点，从根结点开始相减，判断子路径中是否有满足条件的情况。
递归是用和来递归的。
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
    int pathSum(TreeNode* root, int sum) {
        int count = 0;
        vector<TreeNode*> vec;
        helper(count,root,0,sum,vec);
        return count;
    }
    
    void helper(int &count,TreeNode* root,int total,int sum,vector<TreeNode*> vec){
        if(!root) return;
        total += root -> val;
        if(total == sum) ++count;
        vec.push_back(root);
        int temp = total;
        for(int i = 0; i < vec.size()-1;++i){
            temp -= vec[i]->val;
            if(temp == sum) ++ count;
        }
        helper(count,root->left,total,sum,vec);
        helper(count,root->right,total,sum,vec);
        vec.pop_back();
    }
};

完全递归：
注意：只要是递归必须有边界方程限制，即递归结束条件。大多数情况在递归中没有声明初始值的情况（有例外）。
原函数中的递归含义是从每个结点开始的路径。
和函数中的递归指的是从加入新的结点之后的每个子路径。
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
    int pathSum(TreeNode* root, int sum) {
        if(!root) return 0;
        return Sum(root,sum,0) + pathSum(root->left,sum) + pathSum(root ->right, sum);
    }
    
    int Sum(TreeNode* root,int sum, int total){
        if(!root) return 0;
        total += root -> val;
        return (sum == total) + Sum(root->left, sum,total) + Sum(root->right, sum,total);
    }
};