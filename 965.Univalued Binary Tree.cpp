题意：判断一棵树上的所有结点的值是否一致
思路：
1.利用递归首先记录下根结点的值，进入递归
2.如果不存在根结点返回true，再一个个判断递归到的点的值是否等于根结点，如果不等返回false
3.再对左子树和右子树进行递归，返回其返回的结果
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
    bool isUnivalTree(TreeNode* root) {
        int temp = root-> val;
        return dfs(root, temp);
    }
    
    bool dfs(TreeNode* root, int temp){
        if(!root) return true;
        if(root -> val != temp) return false;
        return dfs(root -> left, temp) && dfs(root -> right, temp);
    }
};

Weekly contest 117总结：
1.树的题目在返回递归的值的时候有一点卡壳，要冷静下来想清楚
2.第二题的思路是正确的，但是在中间环节耽误了很长时间因为第一次输出没有得到想要的结果。
后来仔细理了一下发现就是取余的问题，思路是没问题的。
但是没有一次性AC因为还有一种corner cases没有考虑到，这种能自己进行测试的题目在写测试例子的时候也要思考！没有一次AC实在不应该。
3.最后没有时间再继续思考3，4题了，继续思考应该能有结果。在比赛和面试环节都是如此，专注的思考，抓紧时间调试，没到最后不要放弃！