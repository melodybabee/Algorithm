题意：
找到二叉搜索树中第K小的元素
方法一：heap
思路：
1.遇到找第K大或者第K小的元素，首先会想到堆，C++中默认的是最大堆，因此需要转换为最小堆。
2.注意转换为最小堆需要3个变量，priority_queue<int,vector<int>,greater<int>>,堆中元素的值，vector元素集，和排列方式。greater<int>表示从小到大排列。
3.递归BST，任何顺序都可以，后将元素入栈，输出第K个即可。
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
    int kthSmallest(TreeNode* root, int k) {
        priority_queue<int,vector<int>,greater<int>>q;
        helper(root,q);
        for(int i = 1; i < k; ++i){
            q.pop();
        }
        return q.top();
    }
    
    void helper(TreeNode*root, priority_queue<int,vector<int>,greater<int>> &q){
        if(!root) return;
        q.push(root ->val);
        helper(root->left,q);
        helper(root->right,q);
    }
};
方法2:非递归+计数器
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
    int kthSmallest(TreeNode* root, int k) {
        int count = 0;
        stack<TreeNode*>st;
        TreeNode*cur = root;
        while(!st.empty()||cur){
            while(cur){
                st.push(cur);
                cur = cur -> left;
            }
            cur = st.top();
            st.pop();
            ++count;
            if(count == k) return cur -> val;
            cur = cur -> right;
        }
        return 0;
    }
};
方法3:分治法求解
思路：
1.首先找到左子树的结点个数，如果K小于等于这个数字，那么递归左子树。
2.如果等于这个数字，表示是当前根结点所在位置，那么返回根结点的值。
3.如果大鱼这个数字+1，那么递归右子树。
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
    int kthSmallest(TreeNode* root, int k) {
        int count = num(root -> left);
        if(k <= count){
            return kthSmallest(root->left,k);
        }else if (k > count+1){
            return kthSmallest(root -> right, k -count-1);
        }
        return root -> val;
    }
    
    int num(TreeNode*root){
        if(!root) return 0;
        return 1+ num(root->left) + num(root -> right);
    }
};

follow up:
如果频繁的修改树同时频繁的需要查找较小点的话，同样用分治法求解会比较好。
但是每次递归求左子树的结点个数时间复杂度也很高，那么就需要修改原树结点的结构，使其保存包括当前结点和其左右子树所有结点的个数.
思路：
1.自定义一个新树，对每个结点加入一个计算其左右子树一共有多少个结点的变量。
这样每次直接判断K是否在其范围内便知道向哪侧移动。
2.在helper函数中注意判断是否存在左结点，再判断值大或者小。
之前不需要判断是因为如果左没有结点那么返回的值是0，k不会比0还小。
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
    struct MytreeNode{
        int val;
        int count;
        MytreeNode *left;
        MytreeNode *right;
        MytreeNode(int x) : val(x),count(1),left(NULL),right(NULL){}
    };
    
    int kthSmallest(TreeNode* root, int k) {
        MytreeNode *node = build(root);
        return helper(node,k);
        
    }
    
    MytreeNode *build(TreeNode *root){
        if(!root) return NULL;
        MytreeNode *node = new MytreeNode(root -> val);
        node -> left = build(root-> left);
        node -> right = build(root -> right);
        if(node -> left) node -> count += node -> left -> count;
        if(node -> right) node -> count += node -> right -> count;
        return node;
    }
    
    int helper(MytreeNode *node, int k){
        if(node ->left){
            if(k <= node -> left->count){
                return helper(node -> left,k);
            }else if(k > node -> left->count +1){
                return helper(node -> right,k - node ->left->count -1);
            }
            return node -> val;
        }else{
            if(k ==1) return node -> val;
            else return helper(node->right,k-1);
        }
    }
    
};