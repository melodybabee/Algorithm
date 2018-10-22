题意：
096的follow up,输出所有找到的二叉树路径
方法：递归
思路：
1.首先对于1-目标值进行递归，从1开始作为根依次调用，根结点可以从1-n，假设根结点的值为i
2.分别递归建造根的左子树和右子树，左子树的根结点是min到i-1;右子树的根结点是i+1到max;
3.再用根结点为root建造树，注意此步需要分别循环左vector和右vector中的所有树指针
4.如果递归的时候左大于右，那么直接返回NULL
举例：
如果是1-3
那么在1为根结点的时候，1左为空，1右包括以2，3为根的两棵树，分别是2，null，3和3,2,NULL
树的根结点i的右指针需要分别连接上面的两棵树，作为以1为根结点的树
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
    vector<TreeNode*> generateTrees(int n) {
        if(n==0) return {};
        return treeBuild(1,n);
    }
    vector<TreeNode*>treeBuild(int min, int max){
        vector<TreeNode*> ret;
        if(min > max){
            ret.push_back(NULL);
            return ret;
        }
        for(int i = min; i <= max; ++i){
            vector<TreeNode*> left = treeBuild(min,i-1);
            vector<TreeNode*> right = treeBuild(i+1,max);
            for(int j = 0; j < left.size();++j){
                for(int k = 0; k < right.size(); ++k){
                    TreeNode* root = new TreeNode(i);
                    root -> left = left[j];
                    root -> right = right[k];
                    ret.push_back(root);
                }
            }
        }
        return ret;
    }
};
优化：有一个所有返回都是指针类型的写法待学习。