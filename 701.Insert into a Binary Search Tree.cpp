题意：在BST中插入新的结点
方法一：递归
思路：
1.为了避免不破坏根结点便于返回，设置了一个helper函数
2.当递归函数中没有根结点的时候，新建立一个结点，返回
3.否则根据目标值和根结点值的大小开始调用递归函数，注意保持树的连接，即每次调用都需要通过root->left或者root->right进行递归
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        helper(root,val);
        return root;
    }
    
    TreeNode* helper(TreeNode*root, int val){
        if(!root){
            TreeNode *newnode = new TreeNode(val);
            return newnode;
        }
        if(root -> val > val){
            root -> left = helper(root -> left,val);
        }
        if(root -> val < val){
            root -> right = helper(root -> right,val);
        }
        
        return root;
    }
};

优化：不用helper函数在一个函数中
在没有根结点的时候直接返回新的结点即可。
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root) return new TreeNode(val);
        if(root -> val > val) root -> left = insertIntoBST(root -> left, val);
        else root -> right = insertIntoBST(root -> right, val);
        return root;
    }
};

方法2:遍历
思路：
1.注意因为遍历方法是从根结点开始操作，因此需要设置一个dummy指针来操作根结点利于根结点的返回。
2.只要根结点不存在，或者左右子树不存在，那么直接加入新的结点，break;
因此在创建之前需要判断是否已经存在左右子树，存在的话移动，不存在的话插入，最后返回根结点。
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root) return new TreeNode(val);
        TreeNode *cur = root;
        while(true){
            if(cur->val > val){
                if(!cur -> left) {cur -> left = new TreeNode(val);break;}
                cur = cur -> left;
            }else{
                if(!cur -> right) {cur -> right = new TreeNode(val);break;}
                cur = cur -> right;
            }
        }
        return root;
    }
};
