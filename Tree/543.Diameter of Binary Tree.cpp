题意：
找到树任意结点开始的最大路径长度，124的简化版。
方法一：递归，由下至上
思路：
1.本题是找到路径长度，124是找到每个结点值相加之后的最大值。
因此本题的结果一定是从一个叶子结点开始，即不存在负值，到一个叶子结点结束的。124计算结点的值会出现舍弃负值的情况。
共同之处在于都可以跨越根结点。返回的是在计算过程中遇到的最大的值，该变量作为递归函数的引用变量。结果并不是递归函数的返回值。
递归函数的返回值作为阶段性计算结果的较大值，便于后面的运算。
2.本题本身就是求出根结点的左右两个子树的深度和+1，那么递归求解每个根结点的深度即可。
3.从根结点开始递归调用其左右子树的深度，结果值记录下其左子树和右子树的深度与当前结果值中的较大值。
4.结果返回左右子树深度中较大的一个+1，只要有一个结点那么深度就为1。
5.最后返回结果值即可，是过程中左右子树深度和的较大值。
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
    int diameterOfBinaryTree(TreeNode* root) {
        int ret = 0;
        helper(root,ret);
        return ret;
    }
    
    int helper(TreeNode* root, int &ret){
        if(!root) return 0;
        int left = helper(root -> left, ret);
        int right = helper(root -> right,ret);
        ret = max(ret,left+right);
        return max(left,right)+1;
        
    }
};
方法2:用一个map记录下过程中找到的深度值，避免重复计算。本质思路与上述完全相同。
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
    unordered_map<TreeNode*,int> map;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int ret = 0;
        helper(root,ret);
        return ret;
    }
    
    int helper(TreeNode* root, int &ret){
        if(!root) return 0;
        if(map.count(root)) return map[root];
        int left = helper(root -> left, ret);
        int right = helper(root -> right,ret);
        ret = max(ret,left+right);
        map[root] = ret;
        return max(left,right)+1;
        
    }
};

12.11复习：
注意：长度为4个结点的返回值是3，因此只有一个结点时返回的长度时0.
长度定义为边数，不是结点个数。
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
    int diameterOfBinaryTree(TreeNode* root) {
        int ret = 0;
        helper(root,ret);
        return ret;
    }
    
    int helper(TreeNode*root, int &ret){
        if(!root) return 0;
        int left = helper(root -> left, ret);
        int right = helper(root -> right, ret);
        ret = max(ret, left + right);
        return max(left+1, right +1);
    }
};