题意：给二叉树安装照相机，使其能够检测到每个结点的状态，求最少的照相机个数
【重点复习思路】
思路：
1.如果是树上的一个结点，包括了它本身，他的两个子结点和他的父结点，有4种情况
如果是根结点，包括它本身和它的两个孩子，一共有3种情况
如果是叶子结点，包括它本身和他的父结点，一共有2种情况，因此从叶子结点入手比较好
2.那么如果是叶子结点，标记为0，如果是叶子结点的父结点，标记为1，也就是应该放照相机的地方，如果是照相机的父结点，那么标记为2，表示可以覆盖掉。
3.思路是从叶子结点的父结点开始安装照相机，照相机的父结点省略，再上层重新定义为叶子结点。
本质是后序遍历。
4.设置一个全局变量来记录需要安装照相机的个数，dfs返回的是根结点的状态。
如果根结点的状态为0，那么表示需要安装，如果是1，或者2则不需要安装。
5.如果左结点存在，递归左子树，返回值是左子树的状态，右子树同理。
一旦左右子树中有一个为0，表示需要安装相机，同时把该位置的状态改为1
4.如果左右子树中有一个为1，那么该结点的状态为2，否则为叶子结点
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
    int minCameraCover(TreeNode* root) {
        return (dfs(root) == 0 ? 1 : 0) + ret ;
    }
    
    int dfs(TreeNode* root){
        if(!root) return 2;
        int left = dfs(root -> left);
        int right = dfs(root -> right);
        if(left == 0 || right == 0){
            ++ret;
            return 1;
        }
        return left == 1 || right == 1 ? 2 : 0;
    }
};