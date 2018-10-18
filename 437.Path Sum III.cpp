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