题意：类似968
把每个树上的结点上的硬币均匀分布，使得每个结点有且只有一个硬币，问最少的移动步数。
思路：
1.设置一个全局变量进行遍历。
2.如果根结点不存在，那么返回0，开始后序遍历，分别求出左右结点的值，该值表示结点需要的点数，1表示需要减去一个，-1表示需要加上一个
3.结果值需要加上左右结点值的绝对值，即移动的步数，如果有3个硬币的结点，必定会将他的2的移动，那么首先计算以它为源头的移动步数
返回值是该结点本身的值+左结点的值+右结点的值-1，留下一个给自己
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
private:
    int ret = 0;
public:
    int distributeCoins(TreeNode* root) {
        dfs(root);
        return ret;
    }
    
    int dfs(TreeNode* root){
        if(!root) return 0;
        int left = dfs(root -> left);
        int right = dfs(root -> right);
        ret += abs(left) + abs(right);
        return left + right + root->val -1;
    }
};