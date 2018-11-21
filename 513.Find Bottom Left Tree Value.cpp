题意：
找到二叉树中最后一行中最左结点的值。
方法一：BFS
思路：
1.建立一个queue层序遍历树，先把根结点放到队列中，当queue不为空的时候，进入while循环
2.本题的不同之处是需要记录下每层的第一个元素便于后面输出，那么进入while循环之后确定当前queue的长度。
开始for循环，依次找每个结点是否有左右结点，有的话把其push到队列的尾部。每次遍历到第一个结点的时候记录下该点的值。
3.最后返回记录下的值。
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
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*>q;
        q.push(root);
        int res;
        while(!q.empty()){
            int size = q.size();
            for(int i = 0; i < size ;++i){
                TreeNode *t = q.front();
                q.pop();
                if(i == 0) res = t -> val;
                if(t->left) q.push(t->left);
                if(t->right) q.push(t->right);
            }
        }
        return res;
    }
};
方法2:先序遍历性质的强化
1.先序遍历，因为先序遍历的顺序是根，左，右，那么只要遍历到新的一层，那么第一个遍历到的值就是想要求的值。
2.这样用一个变量记录下当前的深度，如果有更大的深度，更新，同时记录下此时结点的值。最后返回结果。
注意：
在helper函数中深度和返回的结果都需要用引用变量，引用变量的意思是一个变量，而不仅仅是一个数值。
因此变量只要更新为新的值之后，就不会因为递归的先后顺序回到原先的值，深度更新到最大之后，递归回到上一层更新后面的同层结点不会再更新。
返回值也记录的是第一位结点的值。
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
    int findBottomLeftValue(TreeNode* root) {
        int depth = 1;
        int res = root -> val;
        helper(root, 1,depth,res);
        return res;
    }
    
    void helper(TreeNode* root, int d, int &depth,int &res){
        if(!root) return;
        if(d > depth){
            depth = d;
            res = root -> val;
        }
        helper(root -> left, d+1, depth, res);
        helper(root -> right, d+1, depth, res);
    }
};