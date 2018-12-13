题意：
找到BST中距离目标值最近的值。
方法一：递归
思路：
1.递归二叉搜索树目标是为了找到target元素左右边界值，那么首先把左边界设置为long_min,右边界设置为long_max
2.从根结点开始递归，如果根大于等于目标值，把右边界更新为根结点的值，那么递归左结点。
如果小于目标值，把左边界更新为根结点的值，递归右结点。
3.左边界和右边界是引用值，因为double的范围较大，为-1.7*10^308 - 1.7*10^308,因此需要用long long的数字记录
4.最后用两个边界值对target做差，哪个近返回哪个
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
    int closestValue(TreeNode* root, double target) {
        long long l = LONG_MIN;
        long long r = LONG_MAX;
        helper(root, target,l,r);
        if(r - target < target -l){
            return r;
        }else{
            return l;
        }
    }
    
    void helper(TreeNode*root, double target, long long &l, long long &r){
        if(!root) return;
        if(root->val >= target){
            r = root-> val;
            helper(root ->left, target,l,r);
        }
        if(root -> val < target){
            l = root -> val;
            helper(root -> right,target,l,r);
        }
    }
};
优化：

方法2：遍历做法：
思路：
1.首先记录下根结点的值，比较根结点的值与目标值之间的差和当前遍历到的结点与目标值之间的差。
如果当前的比根结点的大，那么把结果更新为根结点的值。相当于用结果值和根结点的值作为找最近值之间的两个选项。
2.判断根结点走向，如果目标值更大，向右移动，如果小向左移动。
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
    int closestValue(TreeNode* root, double target) {
        int res = root -> val;
        while(root){
            if(abs(res-target) >= abs(root->val - target)){
                res = root -> val;
            }
            root = target < root->val ? root -> left : root -> right;
        }
        return res;
    }
};

12.13复习：
递归：
注意：
1.用long long来替代int,double的范围很大
2.核心思想是设置左右边界来不断缩小范围
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
    int closestValue(TreeNode* root, double target) {
        long long l = LONG_MIN;
        long long r = LONG_MAX;
        helper(root,target,l,r);
        if(r- target < target - l){
            return r;
        }else return l;
    }
    void helper(TreeNode* root, double target,long long &l,long long &r){
        if(!root) return;
        if(root -> val > target){
            r = root -> val;
            helper(root -> left,target,l,r);
        }else{
            l = root -> val;
            helper(root -> right,target,l,r);
        }
    }
};