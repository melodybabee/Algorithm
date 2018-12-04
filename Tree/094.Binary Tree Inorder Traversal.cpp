题意：树的前序遍历
方法1:递归
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ret;
        inorder(root, ret);
        return ret;
    }
    void inorder(TreeNode* root,vector<int>&ret){
        if(!root) return;
        if(root->left) inorder(root -> left,ret);
        ret.push_back(root->val);
        if(root->right) inorder(root -> right,ret);
    }
};
方法二：遍历
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
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode *p = root;
        vector<int> ret;
        while(!st.empty()||p){
            while(p){
                st.push(p);
                p = p->left;
            }
            p = st.top();
            st.pop();
            ret.push_back(p->val);
            p = p->right;
        }
        return ret;
    }
};
方法三：线索二叉树。threaded binary tree
不用栈不用递归，Morris Traversal
思路：
总体思路：在中序遍历中，将所有为空的右子结点指向中序遍历的下一个结点
1.初始化指针cur指向root
2. 当cur不为空时
如果cur没有左子结点：
a) 打印出cur的值
b) 将cur指针指向其右子节点
如果cur有左子结点：
将pre指针指向cur的左子树中的最右子节点，去寻找最右子结点
3.若pre不存在右子节点，即右子结点为空的时候，将其右子节点指回cur，cur指向其左子节点
若pre有右子节点但是还是跳出while循环，说明pre的右子结点等于cur,之前已经遍历到这一位把它连接到了遍历它之后的下一个结点的位置
那么，将pre的右子节点置空，输出cur的值，将cur指针指向其右子节点

注意：这样一来，所有没有右子结点的值都会有右指针，连接下一位应该输出的值，所以cur一直找他的右子结点就可以了。
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ret;
        TreeNode*pre;
        TreeNode *cur = root;
        if(!root) return ret;
        while(cur){
            if(!cur->left){
                ret.push_back(cur->val);
                cur = cur -> right;
            }else{
                pre = cur->left;
                while(pre ->right && pre -> right != cur) pre = pre -> right;
                if(!pre->right){
                    pre -> right = cur;
                    cur = cur ->left;
                }else{
                    pre -> right = NULL;
                    ret.push_back(cur->val);
                    cur = cur -> right;
                }
            }
        }
        return ret;
    }
};


12.3复习：
递归：
递归方法的过程用最简单的树模拟一下！
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        inorder(root, ret);
        return ret;
    }
    
    void inorder(TreeNode*root, vector<int>&ret){
        if(!root) return;
        inorder(root->left,ret);
        ret.push_back(root->val);
        inorder(root-> right, ret);
    }
};

遍历：
树的遍历需要一个指针进行移动，作为遍历的角色，后进先出，因此用栈。
当栈不为空或者指针存在的时候进入循环。
中序遍历先找到最左结点，输出，再向右移动；右边不存在那么再从栈中输出一个新的结点，判断右结点是否存在。
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> vec;
        stack<TreeNode*> st;
        TreeNode *cur = root;
        while(!st.empty() || cur){
            while(cur){
                st.push(cur);
                cur = cur -> left;
            }
            cur = st.top();
            st.pop();
            vec.push_back(cur->val);
            cur = cur -> right;
        }
        return vec;
    }
};

线索二叉树：threaded binary tree
核心：
1.有两个指针，cur负责遍历当前的位置，对于中序遍历来说，如果没有左子树，那么可以直接输出到结果数组中。
pre负责为cur找到没有右子树的结点的下一个需要遍历的位置在哪里。
2.因此pre的位置是cur的前一位，如果有右子树，找到右子树中的最右结点，连接到cur上。
【注意】需要区分是第一次进入还是第二次进入，因为中序遍历还会回到原来已经遍历的结点上。
第一次进入连接回cur,cur继续向左移动。
但是如果已经连接上，即pre -> right = cur,那么需要把pre -> right置为0.输出cur的值，cur向右移动。
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> vec;
        TreeNode *pre = NULL;
        TreeNode *cur = root;
        while(cur){
            if(!cur->left){
                vec.push_back(cur -> val);
                cur = cur -> right;
            }else{
                pre = cur -> left;
                while(pre -> right && pre -> right != cur) pre = pre -> right;
                if(!pre -> right){
                pre -> right = cur;
                cur = cur -> left;
                }else{
                    pre -> right = NULL;
                    vec.push_back(cur->val);
                    cur = cur ->right;
                }
            }
        }
        return vec;
    }
};
 
