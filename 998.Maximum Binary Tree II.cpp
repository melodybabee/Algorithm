题意：在最大树中插入一个新的结点
方法一：递归
思路：
1.比赛过程中已经分析出来了需要不断对右侧递归，如果是新的结点要添加在左侧
卡在如果递归需要对原根结点进行递归，即递归得到的返回的结点是连着根结点的右侧的，也就避免了需要不断更新根结点的问题
2.如果根结点存在而且插入值小于根结点，那么进入递归。如果大于根结点，说明需要新建一个结点，他的左子树指向根结点，再返回。
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
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        if( root != NULL && root -> val > val){
            root->right = insertIntoMaxTree(root->right, val);
            return root;
        }
        TreeNode *newnode = new TreeNode(val);
        newnode -> left = root;
        return newnode;
    }
};

方法2:遍历
思路：
1.首先创建好一个新的结点，需要用cur来代表根结点进行移动
2.如果需要在根部加入新的结点，那么就直接返回这个新的结点即可
3.否则向右一直while循环到尾部或者val的值大于当前的右侧的地方，相互连接，最后返回根结点
注意：
cur代表是当前遍历到的位置，如果右侧没有结点或者小于val的话，cur不会再次异动
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
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        TreeNode *newroot = new TreeNode(val);
        TreeNode *cur = root;
        if(val > root->val){
            newroot -> left = root;
            return newroot;
        }
        
        while(cur -> right && cur -> right -> val > val){
            cur = cur -> right;
        }
        newroot ->left = cur ->right;
        cur->right = newroot;
        return root;
        
    }
};