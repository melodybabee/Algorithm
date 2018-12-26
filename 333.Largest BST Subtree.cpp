题意：找到二叉树中最大的二叉搜索树的结点个数。
方法一：递归
T(n) = O(n^2);
思路：
1.从根结点开始一个一个判断是否是二叉搜索树，如果是的话，那么计算以这个结点为根的二叉搜索树的大小
2.如果根结点不是，那么返回其左子树和右子树中较大的一个
3.判断是否是二叉搜索树的时候，需要首先规定一个左右边界，如果不在范围内，那么返回false;如果根结点不存在那么返回true
注意此处不在范围内也包括相等，因为二叉搜索树中不能相等。所以如果相等的话那么也是false
在分别判断其左子树和右子树是否满足二叉搜索树
4.输出结点个数的时候不存在根结点返回0，再依次计算左子树的个数+右子树的个数+1
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
    int largestBSTSubtree(TreeNode* root) {
        if(!root) return 0;
        if(isvalid(root,INT_MIN,INT_MAX)) return count(root);
        return max(largestBSTSubtree(root->left),largestBSTSubtree(root->right));
    }
    
    bool isvalid(TreeNode *root, int min, int max){
        if(!root) return true;
        if(root -> val <= min || root -> val >= max) return false;
        return isvalid(root -> left, min, root -> val) && isvalid(root -> right, root -> val, max);
    }
    
    int count(TreeNode *root){
        if(!root) return 0;
        return count(root -> left) + count(root -> right) + 1;
    }
};

方法2:一次遍历【重点复习】
T(n) = O(n);
思路：
1.因为要通过一次遍历判断是否是二叉搜索树，那么从最左结点开始判断调用递归，在对右结点调用递归。
如果左右都不存在，或者已经在二叉搜索树内，那么判断当前结点是否在范围内。
如果不存在左子树或者比左子树的最大值大且不存在右子树或者比右子树的最小值小，那么表示可以增加一个结点，同时更新左右边界
2.如果不在范围内，那么返回左子树和右子树中较大的一个数值
3.最后返回结果值，是一个引用类型的变量
注意：
1.不能声明名字是max或者min的变量，它们都是内置函数
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
    int largestBSTSubtree(TreeNode* root) {
        if(!root) return 0;
        int ret = 0;
        int mn = INT_MIN;
        int mx = INT_MAX;
        bool d = isvalidBST(root,mn,mx,ret);
        return ret;
    }
    
    bool isvalidBST(TreeNode* root, int &mn, int &mx, int &ret){
        if(!root) return true;
        int left_num = 0;
        int right_num = 0;
        int leftmin = INT_MIN;
        int rightmin = INT_MIN;
        int leftmax = INT_MAX;
        int rightmax = INT_MAX;
        bool isleft = isvalidBST(root -> left, leftmin, leftmax, left_num);
        bool isright = isvalidBST(root -> right, rightmin, rightmax, right_num);
        if(isleft && isright){
            if((!root -> left || root -> val > leftmax) && (!root -> right || root -> val < rightmin)){
                ret = left_num + right_num +1;
                mn = root -> left ? leftmin : root -> val;
                mx = root -> right ? rightmax : root -> val;
                return true;
            }
        }
        ret = max(left_num,right_num);
        return false;
    }
};
