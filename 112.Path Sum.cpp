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
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        if(root -> left == NULL && root ->right == NULL) return root -> val == sum;
        
        stack<TreeNode*> st;
        TreeNode* p = root;
        st.push(p);
        while(!st.empty()){
            p = st.top();
            st.pop();
            if(p -> left == NULL && p -> right == NULL && p -> val == sum) return true;
            
            if(p -> right){
                st.push(p ->right);
                p -> right ->val += p -> val;
            }
            if(p -> left){
                st.push(p -> left);
                p -> left ->val += p -> val;
            }
        }
        
        return false;
    }
};
//DFS 非递归
/*
思路：
1.首先判断边界条件，如果根不存在，直接返回false,如果根结点的左右为空，判断根结点的值是否和sum值相等
2.建立stack,放入root，设立一个p指针指向root
3.当stack的值不为空的时候，判断p指向的当前结点，如果p左右都为空，且和与sum相等，则返回true
4.否则如果p有左结点或者有结点的时候，将左／右结点的值变为原有值+p当前的值，目的使叶子结点的值即为该路径上的和，同时将左右结点push到stack中
5.当stack为空的时候如果还没有返回true,则返回false

难点：
1.注意在遍历的过程中，可以把每个结点的值改为从根结点到此结点的路径上所有结点的和，这样判断是否是叶子结点，如果是，用叶子结点与sum比较即可
*/

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
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        if(!root -> left && !root -> right) return root -> val == sum;
        
        int new_sum = sum - root -> val;
        return hasPathSum(root -> left, new_sum) || hasPathSum(root -> right, new_sum);
    }
};
//递归
/*
思路：
1.递归解法首先需要分析问题，找到和为sum的路径，可以用初始的sum遇到结点后以此相减，从根结点开始，判断完成后交给它的左／右子结点再解决子问题
2.递归需要注意防守（即边界条件），当无根或者左右子树为空的时候，返回根结点的值与sum是否相等的bool值
3.再分别返回左子树或者右子树的bool值
时间复杂度为O（n)，因为一共走了n个结点

generally speaking, 当原有的函数变量数不能满足时，可以设置helper函数进行递归，其余在函数本身function大多可以解决问题，因为tree本身就是递归建立的
*/