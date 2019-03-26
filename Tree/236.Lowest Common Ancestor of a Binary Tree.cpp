题意：
找到二叉树的最低公共根(LCA),235题的follow up
思路：
1.与235题的区别是235是一棵二叉搜索树，因此知道p,q会落在哪边，从而直接能够找到LCA
2.那么在这道题中，如果根结点不存在或者p,q为根结点，那么直接返回。后面的子树调用递归。
3.最后的返回结果有三种情况，如果左右子树都存在，那么说明当前根结点就是LCA
4.如果p,q都在左子树，那么返回结果中会返回p,q中较大的那个，右子树返回空，因此此时返回左子树即可。
或者左子树返回p,q的公共结点，即左右子树都存在的子情况，这样右结点为空，因此返回左公共结点即可。
5.右侧的递归结果与左侧同理，或返回左右中较大的数，或者返回p,q的公共结点，左子树为空。
6.因此当左或者右一边存在的时候，返回存在的一边的结果即可。
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q) return root;
        TreeNode*left = lowestCommonAncestor(root -> left, p ,q);
        TreeNode*right = lowestCommonAncestor(root -> right, p , q);
        if(left && right) return root;
        return left? left : right;
    }
};
优化：
在递归的时候如果左存在且不等于p或者q，那么说明此时的左结点已经是我们要求的值，因此直接返回就可以，不用调用右侧递归了。
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q) return root;
        TreeNode*left = lowestCommonAncestor(root -> left, p ,q);
        if(left && left != p && left != q) return left;
        TreeNode*right = lowestCommonAncestor(root -> right, p , q);
        if(right && right != p && right != q) return right;
        if(left && right) return root;
        return left? left : right;
    }
};

12.7复习：
注意：
核心思路就是先左右递归，如果分别在左右两侧，那么返回根结点。如果只在一侧出现，那么返回出现一侧的结点。
注意在递归中重新设置一个新变量作为临时储存的值的方法。
因为是DFS递归，因此如果在左边能找到结果就不需要递归右子树了，那么直接返回结果即可。
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root -> val == p->val || root -> val == q -> val) return root;
        TreeNode *left = lowestCommonAncestor(root -> left,p,q);
        TreeNode *right = lowestCommonAncestor(root -> right,p,q);
        if(left && right) return root;
        else  return left ? left : right;
    }
};
优化：
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root -> val == p->val || root -> val == q -> val) return root;
        TreeNode *left = lowestCommonAncestor(root -> left,p,q);
        if(left && left  != q  && left  != p ) return left;
        TreeNode *right = lowestCommonAncestor(root -> right,p,q);
        if(right && right != q && right != p) return right;
        if(left && right) return root;
        else  return left ? left : right;
    }
};
1.29复习
注意：
问题的本质在于如果在根结点处找到了目标值，那么直接返回，因为这一点先找到的话那么肯定是要求的LCA
再去判断左右是否存在，如果不存在，那么就是另一边作为返回值，如果都存在，那么LCA就是当前递归到的根结点
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        if(root -> val == p -> val) return p;
        if(root -> val == q -> val) return q;
        if(!root -> left && ! root -> right) return NULL;
        TreeNode* l = lowestCommonAncestor(root -> left,p, q);
        TreeNode* r = lowestCommonAncestor(root -> right,p, q);
        if(l && r) return root;
        else 
            return l == NULL ? r : l;
    }
};

3.25复习
注意：
1.目标是找到等于p或者q的值，分成两种情况，一个是pq的公共祖先不是他们当中的值，一个是公共祖先是他们的值
2.那么如果根结点就是p或者q，那么直接返回，否则继续查找记录下来左结点和右结点的值
3.如果左右都存在，说明公共结点应该是当前的根结点。
如果只有一方存在，那么返回存在的一方。
注意：
遍历树的过程也是递归的过程，在判断左右结点是否存在的时候可以直接通过根结点的角度考虑。
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q) return root;
        TreeNode *left = lowestCommonAncestor(root->left,p,q);
        TreeNode *right = lowestCommonAncestor(root->right,p,q);
        if(left && right) return root;
        else return left == NULL ? right : left;
    }
};