题意：
把二叉树转换为带括号形式的二叉树。
方法一：递归
思路：
1.通过观察题意发现，如果根结点的左子树为空而右子树不为空，那么需要添加一对括号，如果右子树为空左子树不为空则不需要。
那么在递归函数中首先判断根结点是否存在，不存在直接返回。
2.在每次输出一个值之前加入左括号，判断是否左子树不存在右子树存在。
3.分别对左右子树调用递归，每轮递归结束之后加上右括号。
4.最后输出的字符串是没有最外侧的括号的，因此在输出之前需要把最外侧的括号删除。
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
    string tree2str(TreeNode* t) {
        if(!t) return "";
        string s ="";
        dfs(s,t);
        return string(s.begin()+1,s.end()-1);
    }
    
    void dfs(string &s,TreeNode *t){
        if(!t) return;
        s += '(' +to_string(t->val);
        if(! t-> left && t -> right) s +="()";
        dfs(s,t->left);
        dfs(s,t->right);
        s += ')';
    }
};
方法2:调用本身的递归函数
思路：
1.首先计算根结点的值，分别递归计算左子树和右子树的结果。
2.如果左右均为空，那么直接返回根结点的已有值。
3.如果左为空而右不为空，那么返回结果+空括号+右结点加上括号的值。
4.如果右为空而左不为空，那么返回左结点加上括号的值。
5.如果左右都不为空，返回结果+左结点加上括号的值+右结点加上括号的值。
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
    string tree2str(TreeNode* t) {
        if(!t) return "";
        string ret = to_string(t -> val);
        string left = tree2str(t->left);
        string right = tree2str(t->right);
        if(left == "" && right == "") return ret;
        if(left == "") return ret + "()(" + right +")";
        if(right == "") return ret +"(" + left+")";
        return ret + "(" + left + ")(" + right + ")";
    }
};