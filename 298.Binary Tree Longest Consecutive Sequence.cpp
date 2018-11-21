题意：
找到二叉树中最长的连续序列。
方法一：递归
思路：
1.在递归函数中的变量属性有根结点，根结点的值，需要返回的结果，当前的计数器。
注意如果求最大或者最小一般都有两个计数器，一个作为结果取较大，一个作为遍历过程中的值。
2.进入递归如果根不存在直接返回，如果遍历到的根结点的值等于递归值（即其父结点的值）+1，计数器+1
3.如果不满足+1的情况，计数器重新置为1。注意因为不满足情况和单结点都是为1，此步需要重点强调。
4.结果取较大值，分别对左子树和右子树调用递归，注意左结点和右结点需要和当前根结点的值进行比较判断，所以递归函数中的值仍然是当前根结点的值。
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
    int longestConsecutive(TreeNode* root) {
        if(!root) return 0;
        int count = 0;
        helper(root,root->val,count,0);
        return count;
    }
    
    void helper(TreeNode* root, int value,int &count,int temp){
        if(!root) return;
        if(root->val == value +1)++temp;
        else temp = 1;
        count = max(count,temp);
        helper(root->right,root -> val,count,temp);
        helper(root ->left,root -> val,count,temp);
    }
};
方法二：divide and conquer
1.分别从左右子树入手进行递归，当左右子树存在的时候，初始的长度为1，如果没有满足+1的条件，进入递归的时候的值仍然为1。
如果满足+1的条件，那么长度+1进入递归。
2.返回计算结果中较大的值。
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
    int longestConsecutive(TreeNode* root) {
        if(!root) return 0;
        int res = 0;
        helper(root,1,res);
        return res;
    }
    
    void helper(TreeNode* root, int length, int &res){
        res = max(length,res);
        if(root -> left){
            if(root-> left -> val == root -> val +1) helper(root->left,length+1, res);
            else helper(root -> left,1,res);
        }
        if(root -> right){
            if(root-> right -> val == root -> val +1) helper(root->right,length+1, res);
            else helper(root -> right,1,res);
        }
    }
};
方法3:【存疑】
思路：
1.建立一个队列放入根，如果左右之中有满足+1条件的，指针沿着该方向走，如果存在反方向的结点，那么把该结点push到队列中，为了不丢掉任何一种情况。
2.存在+1就在循环结束之后总长度+1进入递归。
3.在返回的结果中返回较大值，同时如果该指针仍然存在结点，但是已经不满足+1，那么也要push到队列中。
问题：
1.在内部while循环的时候，只有先左后右才能AC，先右后左就不行，没有办法实现+1，没看出来问题出在哪。对换左右就没问题了。
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
    int longestConsecutive(TreeNode* root) {
        if(!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int ret = 0;
        while(!q.empty()){
            int len = 1;
            TreeNode *t = q.front();
            q.pop();
            while((t->right && t->right->val == t->val + 1) || (t->left && t->left->val == t ->val +1)){
                if(t -> left && t ->left -> val == t->val+1){
                    if(t -> right) q.push(t -> right);
                    t = t -> left;
                }else if(t -> right && t ->right -> val == t ->val+1) {
                    if(t -> left) q.push(t -> left);
                    t = t-> right;
                }
                ++len;
            }
            ret = max(ret,len);
            if(t->left)q.push(t->left);
            if(t->right) q.push(t->right);
            
        }
        return ret;
    }
};