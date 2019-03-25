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

3.23复习：
注意：
1.abs()中传入是什么类型的值就是什么类型的结果,abs()之前要考虑正负数的情况，但是抽象含义上绝对值就表示了到某个数之间的距离
2.注意初始值的设置，要返回的值的初始类型是什么，注意越界情况
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
        vector<int>res;
        helper(res,root);
        double count = (double)INT_MAX;
        int val = res[0];
        for(int i = 0; i < res.size(); ++i){
            if(abs(target-res[i]) < count){
                val = res[i];
                count = abs(res[i]-target);
            }
        }
        return val;
    }
    
    void helper(vector<int>&res, TreeNode* root){
        if(!root) return;
        helper(res,root->left);
        res.push_back(root->val);
        helper(res,root->right);
    }
};

遍历：
注意：
1.核心问题在于从根结点开始记录下来结果值，该结果值依次与遍历到的每个结点进行比较
2.遍历的结点的移动方向是根据BST的性质左右移动的，不断夹击
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
        int ret = root -> val;
        while(root){
            if(abs(ret - target) >= abs(root -> val - target)){
                ret = root->val;
            }
            root = root -> val > target ? root->left : root->right;
        }
        return ret;
    }
};
递归写法：
注意：
1.double范围远大于int和long long
int   -2147483648 ~ +2147483647   (4 Bytes) 4*8 = 32字节， -2^31 ~ 2^31-1
为什么-1: https://blog.csdn.net/daiyutage/article/details/8575248
long long         -9223372036854775808 ~ +9223372036854775807    (8 Bytes) -2^63~2^63-1
2.递归目的是找到左右边界的范围，不断缩小范围
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
        return target - l > r - target ? r : l;
    }
    
    void helper(TreeNode* root, double target, long long &l, long long &r){
        if(!root) return;
        if(root -> val < target){
            l = root -> val;
            helper(root->right, target, l , r);
        }else{
            r = root -> val;
            helper(root->left,target,l,r);
        }
    }
};