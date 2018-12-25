题意：二叉树偷窃
方法一：递归
思路：
1.题意是任何相邻的结点不能连续偷窃，那么有两种情况，一个是根结点加上除了左右子树结点的和，一个是左右子树结点和不包括根结点的值
2.基于上述的思路那么对二叉树从根结点进行递归，一种情况是根结点的值加上隔过左右结点取后面的值，一个是所有结点的值
对这两种情况进行递归调用
3.递归的中止条件是如果不存在根结点返回0，另外需要一个哈希表来记录下每个计算过的值，如果能找到那么直接返回
注意map在递归函数中是引用类型
4.如果在map中不能查找到，那么输入对应的map中。最后返回两种情况下值较大的一个
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
    int rob(TreeNode* root) {
        unordered_map<TreeNode*,int>map;
        return helper(root, map);
    }
    
    int helper(TreeNode*root,unordered_map<TreeNode*,int>&map){
        if(!root) return 0;
        if(map.count(root)) return map[root];
        int val = 0;
        if(root -> left){
            val += helper(root -> left -> left,map) + helper(root -> left -> right,map);
        }
        if(root -> right){
            val += helper(root -> right -> left, map) + helper(root -> right -> right, map);
        }
        val = max(val + root -> val, helper(root->left,map)+helper(root -> right, map));
        map[root] = val;
        return val;
    }
};
方法二：递归简化
思路：
1.本题的核心思想就是把根结点和与它相邻的左右结点分开来计算
2.因此用根结点进入递归，对其左右结点继续调用递归，返回值是根结点+隔层结点 与 根的左右结点和中的较大值。
3.注意计算左右结点的时候要把l r变量设置为引用值，因为在递归函数中声明了下一层的变量，那么每次改变都要改变新的该值，不然会一直为0.
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
    int rob(TreeNode* root) {
        int l = 0;
        int r = 0;
        return helper(root,l,r);
    }
    
    int helper(TreeNode*root, int&l, int&r){
        if(!root) return 0;
        int ll = 0, lr = 0, rl = 0, rr = 0;
        l = helper(root-> left, ll, lr);
        r = helper(root -> right, rl,rr);
        return max(root->val+ll+lr+rl+rr, l+r);
    }
};
