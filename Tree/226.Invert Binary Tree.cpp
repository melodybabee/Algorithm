递归方法；
T（O） = O（n), S(O) = O(h), h is the height of the tree
思路：
1.有关tree的问题都可以通过递归实现，注意边界条件，即当根结点不存在的以后返回NULL
2.从上至下分解问题：
只要把所有结点的左右子树对调，且把所有左子树和右子树的子树也进行对调即可
3.从下往上返回结果：
会从叶子结点开始依次向上返回，最后处理根结点左右结点，因此最终返回root即可
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
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return NULL;
        invertTree(root->left);
        invertTree(root->right);
        TreeNode* temp = root -> right;
        root -> right = root ->left;
        root -> left = temp;
        return root;
    }
};

遍历方法：前序遍历
T（O） = O（n), S(O) = O(n)
注意：
1.queue的类型是TreeNode*
2.遍历用到while判断条件的时候一般是queue不为空，当queue为空的时候可以return
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
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return NULL;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode *head = q.front();
            q.pop();
            if(head->left) q.push(head->left);
            if(head->right) q.push(head->right);
            
            TreeNode *temp = head ->right;
            head -> right = head ->left;
            head -> left = temp;
        }
        return root;
    }
};

12.12复习：
注意：
1.因为要先判断是否存在再转换，因此先调用递归再用一个temp对左子树和右子树进行交换，最后返回根结点。-
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
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return NULL;
        invertTree(root -> right);
        invertTree(root -> left);
        TreeNode *temp = root -> left;
        root -> left = root -> right;
        root-> right = temp;
        return root;
    }
};
遍历做法：
同样需要交换。
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
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return NULL;
        queue<TreeNode*>q{{root}};
        while(!q.empty()){
            TreeNode *temp = q.front();
            q.pop();
            if(temp ->left)q.push(temp->left);
            if(temp ->right) q.push(temp->right);
            TreeNode *p = temp -> left;
            temp ->left = temp -> right;
            temp -> right = p;
        }
        return root;
    }
};