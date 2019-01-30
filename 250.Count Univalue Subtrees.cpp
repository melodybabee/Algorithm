题意：
找到树中所有结点的值都相等的子树的个数
方法一：完全递归
思路：
1.设置一个全局变量来作为结果的计数器，对每个根结点调用helper函数判断他的值以及他的子结点们的值是否与他相等
2.再依次对每一个子结点递归调用helper函数，最后返回计数器的值
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
    int count = 0;
public:
    int countUnivalSubtrees(TreeNode* root) {
        if(!root) return count;
        if(helper(root,root->val)) ++count;
        countUnivalSubtrees(root->left);
        countUnivalSubtrees(root->right);
        return count;
    }
    bool helper(TreeNode* root, int value){
        if(!root) return true;
        return root->val == value && helper(root->left,value) && helper(root->right,value);
    }
};
方法2:记录下来左右结点的状态避免重新判断
思路：
1.遇到树的题目先用1个结点，2个结点和3个结点举例子，能解决大部分问题
2.用bool类型的数字来分别记录左右结点的状态，因为左右结点用true和false进行标记，所以只有当左右为true,或者左边不存在/根结点的值等于左边，以及右边不存在/根结点的值等于右边的时候计数器+1，返回true
3.如果不满足情况返回false
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
    int countUnivalSubtrees(TreeNode* root) {
       int ans = 0;
       helper(root,ans);
       return ans;
    }
    bool helper(TreeNode* root, int&ans){
        if(!root) return true;
        bool left = helper(root->left, ans);
        bool right = helper(root->right,ans);
        if(left && right && (!root->right || root->val == root->right-> val) && (!root -> left || root->val == root->left->val)){
            ++ans;
            return true;
        }
        return false;
    }
};