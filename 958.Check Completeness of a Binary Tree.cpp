题意：判断一棵树是否是完全二叉树
思路：遍历
1.核心思想是完全二叉树层序遍历只要遇到了空的结点那么它后面应该都是空的结点，如果不是空的结点那么就返回false
2.那么对二叉树进行层序遍历。层序遍历，分别对左结点和右结点进行入队列。
注意取出队列中的第一个元素作为判断是否能够进入循环，当为空的时候跳出第一个循环进入第二个循环
3.第二个循环判断栈顶元素是否是空，只要还存在返回false,否则返回true
注意：
注意区分栈为空和栈顶元素为空但是栈不为空。
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
    bool isCompleteTree(TreeNode* root) {
        if(!root)return true;
        queue<TreeNode*>q;
        q.push(root);
        TreeNode* temp = q.front();
        while(temp){
            q.push(temp -> left);
            q.push(temp -> right);
            q.pop();
            temp = q.front();
        } 
        while(!q.empty()){
            if(q.front()) return false;
            q.pop();
        }
        return true;
    }
};