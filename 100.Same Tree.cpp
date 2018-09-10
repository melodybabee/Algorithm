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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == NULL && q == NULL) return true;
        if(p == NULL) return false;
        if(q == NULL) return false;
        if(p -> val != q-> val) return false;
        
        //cout << p -> val << endl;
        
        return isSameTree(p -> left, q -> left) && isSameTree(p -> right, q -> right);
        
        
    }
};

/*
思路：
1.判断当前结点p,q值是否相等，如果不等，直接返回false,否则依次递归循环左结点和右结点

注意：
1.本题中true的条件是所有循环的过程中，不出现false的情况，直到p,q都为空为止
2.最后的递归return需要同时返回左子树和右子树，用到"&&"这个符号
如果写成了return isSameTree(p -> left, q -> left)；
return isSameTree(p -> right, q -> right);
会只返回左子树，接着return true or false, 不返回右子树
3.注意if语句的顺序，因为有可能p,q在过程中为空，不存在p -> val和q -> val的情况，因此需要放在最后

*/