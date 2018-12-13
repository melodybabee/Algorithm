题意：
找到二叉搜索树中目标结点下一个结点位置。
方法一：中序遍历
思路：
1.遇到BST首先想到中序遍历的性质，运用性质做题。
2.对树进行中序遍历，如果找到了，flag置为true,返回下一位。如果没有下一位返回NULL。
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        stack<TreeNode*> st;
        TreeNode *cur = root;
        bool flag = false;
        while(!st.empty() || cur){
            while(cur){
                st.push(cur);
                cur = cur -> left;
            }
            cur = st.top();
            st.pop();
            if(flag) return cur;
            if(cur == p) flag = true;
            cur = cur -> right;
        }
        return NULL;
    }
};

方法2:递归
思路：
1.设置两个变量，一个用来记录与目标的指针结点是否匹配，一个用来返回其根结点。
2.递归实现中序遍历的过程，如果找到了目标值，那么返回的结果为当前的根结点，如果没有找到，用pre记录下当前的根结点。
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
private:
    TreeNode *suc = NULL;
    TreeNode *pre = NULL;
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root) return NULL;
        inorder(root,p);
        return suc;
    }
    
    void inorder(TreeNode*root, TreeNode* p){
        if(!root) return;
        inorder(root -> left, p);
        if(pre == p)suc = root;
        pre = root;
        inorder(root -> right,p);
    }
};
方法3:利用BST性质
1.因为BST是左小于中小于右，那么从根结点开始判断，如果根结点的值大于目标结点，记录下该根结点，向左移动；如果小于等于，向右移动。
目标是找到比目标结点大的结点位置。
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode*ret = NULL;
        while(root){
            if(root->val > p -> val){
                ret = root;
                root = root -> left;
            }else{
                root = root -> right;
            }
        }
        return ret;
    }
};

方法3同理：
注意：
1.当小于等于的时候对根右结点调用递归，找到其下一位。
2.当大于时，用一个结点记录下其调用左子树后的值，如果不存在，返回根结点，存在的话返回左结点。
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root) return NULL;
        if(root->val <= p -> val){
            return inorderSuccessor(root -> right, p);
        }else{
            TreeNode *left = inorderSuccessor(root -> left,p);
            return left? left : root;
        }
    }
};

12.12复习：
递归方法：
注意：因为p是树中的一个值，因此肯定存在，不存在p不存在的情况。
那么就是找到比它大的下一个值。和根结点比较，如果大，向右移动，如果小，还需要先保留下根结点的值。
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root) return NULL;
        if(root ->val <= p -> val) return inorderSuccessor(root -> right,p);
        else {
            TreeNode *temp = inorderSuccessor(root ->left,p);
            return temp ? temp :root;
        }
    }
};
要找到比p大的值
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode *temp = NULL;
        while(root){
            if(root -> val <= p -> val){
                 root = root -> right;
            }else{
                temp = root;
                root = root -> left;
            }
        }
        return temp;
    }
};
利用BST中序遍历的性质进行比较！
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        stack<TreeNode*>st;
        TreeNode*cur = root;
        bool flag = false;
        while(!st.empty() || cur){
            while(cur){
                st.push(cur);
                cur = cur ->left;
            }
            cur = st.top();
            st.pop();
            if(flag) return cur;
            if(cur == p) flag = true;
            cur = cur ->right;
        }
        return NULL;
    }
};