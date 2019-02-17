题意：
判断给出的树上的两个结点是否是非父结点但是同层的
思路：
1.因为题目中的要求是判断两个结点是否是相同的，同时判断两个结点所在的层数
2.那么建立一个方法找到每个结点的父结点，注意不能同时返回，因为如果有0的话会自动返回0，需要返回非0的结点值
3.再分别找到每个结点所在的层数，返回不是0的层数
4.最后分别判断即可
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
    bool isCousins(TreeNode* root, int x, int y) {
        int parentx = findparent(root,x);
        int parenty = findparent(root,y);
        int depthx = finddepth(root,x,0);
        int depthy = finddepth(root,y,0);
        if(depthx == depthy && parentx != parenty) return true;
        else return false;
    }
    
    int findparent(TreeNode *root, int x){
        if(!root) return 0;
        if((root->left && root -> left -> val == x) ||(root->right && root -> right ->val == x)) return root -> val;
        return findparent(root->left,x) == 0 ?  findparent(root->right,x) : findparent(root->left,x);
    }
    
    int finddepth(TreeNode *root, int x, int depth){
        if(!root) return 0;
        if(root -> val == x) return depth;
        return finddepth(root->left,x,depth+1) == 0 ? finddepth(root->right,x,depth+1) :finddepth(root->left,x,depth+1);
    }
};
