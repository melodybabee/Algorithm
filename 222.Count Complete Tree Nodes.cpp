题意：计算完全二叉树的结点个数
方法一：正常递归
TLE
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
    int countNodes(TreeNode* root) {
        if(!root) return 0;
        int count = 1;
        helper(root,count);
        return count;
    }
    
    void helper(TreeNode* root, int &count){
        if(!root) return;
        if(root-> left){
            ++count;
            helper(root->left,count);
        }
        if(root -> right){
            ++count;
            helper(root -> right, count);
        }
    }
};
方法二：利用完全二叉树的性质
补充：
********************************
完全二叉树 complete binary tree
对于一颗二叉树，假设其深度为d（d>1）。除了第d层外，其它各层的节点数目均已达最大值，且第d层所有节点从左向右连续地紧密排列，这样的二叉树被称为完全二叉树；
完全二叉树从根结点到倒数第二层满足完美二叉树，最后一层可以不完全填充，其叶子结点都靠左对齐。
********************************
完美二叉树 perfect binary tree
二叉树的第i层至多拥有2^(i-1)个节点数；深度为k的二叉树至多总共有2*k-1个节点数(leetcode中根结点的层数为1），而总计拥有节点数匹配的，称为“满二叉树”；
********************************
完满二叉树 full binary tree
所有非叶子结点的度都是2.
完美二叉树一定是完全二叉树，而完全二叉树不一定是完美二叉树。
思路：
1.根据上面的性质，如果一棵树是满二叉树，即左子树的高度等于右子树的高度。
那么他的结点总数是2的高度次幂-1，找到其左子树的高度即可。leetcode中根结点的层数是1
2.如果不是满二叉树，左右子树的高度不同，那么调用递归找到其左子树的所有结点个数+右子树的结点个数+根结点（1）为总结点个数
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
    int countNodes(TreeNode* root) {
        int left = leftHeight(root);
        int right = rightHeight(root);
        if(left == right) return pow(2,left)-1;
        return countNodes(root->left) + countNodes(root->right)+1;
    }
    int leftHeight(TreeNode* root){
        if(!root )return 0;
        return 1+leftHeight(root -> left);
    }
    int rightHeight(TreeNode* root){
        if(!root )return 0;
        return 1+rightHeight(root -> right);
    }
};
方法3:方法2的另一种写法
思路：
1.对原方法进行递归调用，设置左右指针指向根结点，依次找到最左结点和最右结点，比较，如果相等，直接返回结点数
2.如果不等，那么调用左子树和右子树分别求结点数，再加上根结点的1
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
    int countNodes(TreeNode* root) {
        TreeNode*leftnode = root;
        TreeNode*rightnode = root;
        int left = 0;
        int right = 0;
        while(leftnode){
            ++left;
            leftnode = leftnode -> left;
        }
        while(rightnode){
            ++right;
            rightnode = rightnode -> right;
        }
        if(left == right) return pow(2,left)-1;
        return countNodes(root -> left) + countNodes(root -> right) +1;
    }
};