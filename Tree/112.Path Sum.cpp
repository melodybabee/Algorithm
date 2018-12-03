题意：
找到二叉树中是否有和等于目标值的一条路径，如果有，返回true,没有返回false
思路：
1.首先判断边界条件，如果根不存在，直接返回false,如果根结点的左右为空，判断根结点的值是否和sum值相等
2.建立stack,放入root，设立一个p指针指向root
3.当stack的值不为空的时候，判断p指向的当前结点，如果p左右都为空，且和与sum相等，则返回true
4.否则如果p有左结点或者有结点的时候，将左／右结点的值变为原有值+p当前的值，目的使叶子结点的值即为该路径上的和，同时将左右结点push到stack中
5.当stack为空的时候如果还没有返回true,则返回false
难点：
1.注意在遍历的过程中，可以把每个结点的值改为从根结点到此结点的路径上所有结点的和，这样判断是否是叶子结点，如果是，用叶子结点与sum比较即可
2.0复习：
注意与递归不同，递归是每次用总和相减，最后判断最后一个值是否等于剩余值。
而遍历的做法是每次更新结点的值，使当前结点的值等于从根结点到当前位置的和，最后判断最后一个结点是否等于目标值。
注意两种方法思路的扩展。
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

法2:递归
思路：
1.递归解法首先需要分析问题，找到和为sum的路径，可以用初始的sum遇到结点后以此相减，从根结点开始，判断完成后交给它的左／右子结点再解决子问题
2.递归需要注意防守（即边界条件），当无根或者左右子树为空的时候，返回根结点的值与sum是否相等的bool值
3.再分别返回左子树或者右子树的bool值
时间复杂度为O（n)，因为一共走了n个结点
generally speaking, 当原有的函数变量数不能满足时，可以设置helper函数进行递归，其余在函数本身function大多可以解决问题，因为tree本身就是递归建立的
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        if(!root -> left && !root -> right) return root -> val == sum;
        
        int new_sum = sum - root -> val;
        return hasPathSum(root -> left, new_sum) || hasPathSum(root -> right, new_sum);
    }
};

2.0复习
思路：
1.二叉树都能用递归的方法解决问题，把从根结点的问题分解为根左和根右依次解决
2.类似DFS回溯的思想，首先写清楚边界条件，根不存在返回false,如果左右都为空判断是否和目标值相等，再进入左右子树的递归中
注意：
在递归函数中尽量不要初始某个变量，因为这样每次进入递归都是初始值
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        TreeNode *p = root;
        if(!root) return false;
        if(!p-> left && !p -> right) return p->val == sum;
        int newsum = sum - p-> val;
        return hasPathSum (p -> left, newsum) || hasPathSum (p -> right, newsum);
    }
};

12.2复习：
这么简单的题目竟然不能一次AC，还做了好几遍。
不要依靠记忆，每道题当作新的去思考，遇到没有想通的就看问题在哪里，和刷几遍、什么难度都没关系。
注意：
递归一定先想清楚边界条件，不存在根结点返回false,判断叶子结点是否和sum相等。
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
        if(!root -> left && ! root -> right) return root ->val == sum;
        return hasPathSum(root-> left, sum - root->val) || hasPathSum(root -> right, sum - root->val);
    }
};
迭代写法，逐层加和，判断最后的和是否相等，和递归的思路是反着的。
运用queue更好是因为满足先到先操作的性质，stack本题也可以做，但是没有需要后进先出的性质。
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
        if(!root -> left && !root -> right) return root -> val ==sum;
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            TreeNode *temp = q.front();
            q.pop();
            if(!temp -> left  && ! temp -> right && temp -> val == sum) return true;
            if(temp -> left){
                temp -> left->val += temp -> val;
                q.push(temp ->left);
            }
            if(temp -> right){
                temp -> right->val += temp -> val;
                q.push(temp ->right);
            }
        }
        return false;
    }
};