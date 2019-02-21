题意：
把一个二叉树复原成二叉搜索树
方法一： 中序遍历两个数组递归
T(n) = O(n^2);S(n)= O(n);
思路：
1.首先需要中序遍历原二叉树所有的结点和结点的值，把结点存储到一个类型为TreeNode*的vector中，把值存入int类型的vector中
2.把值进行sort排序，这样值就满足二叉搜索树的规律了
3.用for循环遍历把每个结点依次放上vector中的主
注意：
1.二叉搜索树中的中序遍历结点的值是由小到大的，为二叉搜索树的性质
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
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> list;
        vector<int> value;
        findValue(root,list,value);
        sort(value.begin(),value.end());
        for(int i = 0 ; i < list.size();++i){
             list[i] -> val = value[i];
        }
        
    }
    void findValue(TreeNode* root, vector<TreeNode*>&list,vector<int>&value){
        if(!root) return;
        findValue(root->left,list,value);
        list.push_back(root);
        value.push_back(root -> val);
        findValue(root->right,list,value);
    }
};
方法2:指针中序遍历
T(n) = O(n);S(n)= O(n);
思路：
1.本题中说了Two elements of a binary search tree (BST) are swapped by mistake.因此是有两个错序的数字。因为二叉搜索树势递增的数列，因此在一个递增的数列中找到两个逆序的数字进行交换即可.
2.对树进行中序遍历，pre指向当前遍历到的结点的前一位，first表示第一位错乱的数字，second表示第二位错乱的数字
3.在应该输出结点值的地方判断结点值大小，如果first不存在，把first设置为当前位，second设置为需要交换的位置。
4.在递归结束以后如果first,second都存在的话直接交换。
class Solution {
public:
    TreeNode* first = NULL;
    TreeNode* second = NULL;
    TreeNode* pre = NULL;
    void recoverTree(TreeNode* root) {
        find(root);
        if(first && second) swap(first -> val, second -> val);
    }
    void find(TreeNode* root){
        if(!root) return;
        find(root -> left);
        if(!pre) pre = root;
        else{
            if(pre -> val > root -> val){
                if(!first) first = pre;
                second = root;
            }
            pre = root;
        }
        find(root -> right);
    }
};
方法3:线索二叉树
T(n) = O(n);S(n)= O(1);
注意：一旦用到递归的方法，那么空间复杂度就不是线性的，因此如果要求是线性的空间复杂度，那么应该首先考虑线索二叉树。
思路：
1.运用线索二叉树的中序遍历方法
2.同样是找到first和second两个错位的元素进行交换即可
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode*pre = NULL;
        TreeNode*first = NULL;
        TreeNode*second = NULL;
        TreeNode *parent = NULL;
        TreeNode *cur = root;
        while(cur){
            if(!cur -> left){
                if(parent && parent-> val > cur -> val){
                    if(!first) first = parent;
                    second = cur;
                }
                parent = cur;
                cur = cur-> right;
            }else{
                pre = cur -> left;
                while(pre -> right && pre -> right != cur){
                    pre = pre -> right;
                }
                if(!pre->right){
                    pre -> right = cur;
                    cur = cur ->left;
                }else{
                    pre->right = NULL;
                    if(parent && parent-> val > cur -> val){
                        if(!first) first = parent;
                        second = cur;
                    }
                    parent = cur;
                    cur = cur -> right;
                }
            }
        }
        if(first && second) swap(first->val,second -> val);
    }
};

2.20复习：
注意：
1.因为题目中说了是两个元素，所以设置两个指针找到两个元素，进行交换即可
first second作为交换的两个元素，cur表示当前遍历到的元素，进行中序遍历
2.注意只有当first不存在的时候才把first赋值，说明这个元素的位置一定不对。但是它与哪个元素进行交换要在遍历之后才能得出，second表示的是需要与它交换的位置。
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
    TreeNode *first = NULL;
    TreeNode *second = NULL;
    TreeNode *cur = NULL;
    void recoverTree(TreeNode* root) {
        recover(root);
        if(first && second) swap(first->val,second->val);
    }
    
    void recover(TreeNode *root){
        if(!root) return;
        recover(root->left);
        if(!cur){
            cur = root;
        }else{
            if(cur -> val > root->val){
                // 注意此处需要判断first,只有不存在的时候才进行赋值，表示这个值的位置不对，后面需要找到与它交换的位置，即后面比cur更小的值
                if(!first)first = cur;
                second = root;
            }
            cur = root;
        }
        recover(root->right);
    }
};
方法2:线索二叉树
注意：
1.first仍然表示第一个位置不对需要向后换的元素，second表示后面较小的元素
parent表示当前需要和遍历到的结点比较大小的结点位置
pre用来对树进行预处理，即把树进行中序遍历连接在一起
2.注意在预处理过程中，分清楚是右结点不存在了还是已经和下一个位置连接在一起了，需要分情况讨论
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
    void recoverTree(TreeNode* root) {
        TreeNode *cur = root;
        TreeNode *pre = NULL;
        TreeNode *first = NULL;
        TreeNode *second = NULL;
        TreeNode *parent = NULL;
        while(cur){
            if(!cur->left){
                if(parent && parent -> val > cur->val){
                    if(!first) first = parent;
                    second = cur;
                }
                parent = cur;
                cur = cur->right;
            }else{
                pre = cur->left;
                while(pre->right && pre->right != cur){
                    pre = pre ->right;
                }
                if(!pre->right){
                    pre->right = cur;
                    cur = cur ->left;
                }else{

                    pre->right = NULL;
                    if(parent && parent -> val > cur->val){
                        if(!first) first = parent;
                        second = cur;
                    }
                    parent = cur;
                    cur = cur->right;
                }
            }
        }
        
        if(first && second) swap(first->val,second->val);
    }
};
