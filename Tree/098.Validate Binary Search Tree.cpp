题意：
判断给出的树是不是一棵二叉搜索树
方法一：递归
思路：
1.把最大值和最小值作为递归的边界，判断左结点是否小于等于最大值，以及右结点是否大于等于最小值
2.把当前结点的位置分别更新为下一个左结点的最大值和下一个右结点的最小值
注意：
1.因为有可能会超出int范围，因此本题中要用long long
2.注意二叉搜索树的左右结点也可以等于根结点，这也是有效的二叉树
3.本题中二叉搜索树表示为左结点都小于根结点的值，右结点的值都大于根结点的值
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
    bool isValidBST(TreeNode* root) {
        return isBST(root, LONG_MIN, LONG_MAX);
    }
    bool isBST(TreeNode* root, long long min, long long max){
        if(!root) return true;
        if(root->val <=  min || root -> val >= max) return false;
        return isBST(root->left, min, root -> val) && isBST(root->right, root-> val, max);
    }
};
方法二：中序遍历，存入一个新数组中
思路：
1.对二叉树进行中序遍历，把遍历到的点都放入数组中，再遍历数组进行循环，如果前一位大于等于后一位，返回false,否则返回true
注意：
1.本题中满足线索二叉树的要求是左<=中<=右，如果左为空，中和右相等也可以满足，但是通常情况下这种情况不满足条件
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        vector<int> vec;
        findValue(root,vec);
        for(int i = 1; i< vec.size();++i){
            if(vec[i-1] >= vec[i]) return false;
        }
        return true;
    }
    
    void findValue(TreeNode* root,vector<int>&vec){
        if(!root) return;
        findValue(root->left,vec);
        vec.push_back(root->val);
        findValue(root -> right,vec);
    }
};
方法三：中序遍历，设定一个pre指针指向前一位，进行比较
1.同样对二叉树进行中序遍历，设置一个pre结点来记录当前值的前一位
2.默认ret=1,用前一位的值与当前值进行比较，如果根结点的值小于等于前一位，那么ret=0;
3.最终只有当ret=1的时候，返回true
注意：
1.因为pre结点需要保留变量的值，因此需要设置为全局变量
2.注意ret为一个全局变量，因此在每次递归调用的时候调用的是一个引用值
3.本题中只要ret变为0，那么就会返回false,只有当全是1的时候才会返回true
class Solution {
public:
    TreeNode* pre;
    bool isValidBST(TreeNode* root) {
        pre = NULL;
        int ret = 1;
        findValue(root,ret);
        if(ret == 1) return true;
        else return false;
    }
    
    void findValue(TreeNode* root, int &ret){
        if(!root) return;
        findValue(root -> left,ret);
        if(!pre) pre = root;
        else{
            if(root -> val <= pre -> val) ret = 0;
            pre = root;
        }
        findValue(root -> right,ret);
    }
};
方法4:非递归，栈
思路：
1.中序遍历首先先把所有的左结点push进栈，如果没有左结点了，取出顶部元素
2.用pre来保存之前循环到的位置，如果当前值小于等于pre的值,那么返回false
3.否则移动pre至当前结点，根结点指向当前结点的右结点
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*>st;
        TreeNode *p = root;
        TreeNode *pre = NULL;
        while(!st.empty()|| p){
            while(p){
                st.push(p);
                p = p -> left;
            }
            TreeNode*temp = st.top();
            st.pop();
            if(pre && temp -> val <= pre->val) return false;
            pre = temp;
            p = temp -> right;
        }
        return true;
    }
};
方法5:线索二叉树
思路：
1.parent指针指向的是需要判断的值的前一位，cur指向的是当前结点，用来比对大小
2.pre用来对没有右子树的结点进行回连，使其连接回当前的结点，即没有右子树的结点遍历完左结点会返回其根
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(!root) return true;
        TreeNode* cur = root;
        TreeNode* pre = NULL;
        TreeNode* parent = NULL;
        bool flag = true;
        while(cur){
            if(!cur -> left){
                if(parent && parent-> val >= cur -> val) flag = false;
                parent = cur;
                cur = cur -> right;
            }else{
                pre = cur -> left;
                while(pre -> right && pre -> right != cur) pre = pre -> right;
                if(!pre->right){
                    pre -> right = cur;
                    cur = cur -> left;
                }else{
                    pre ->right = NULL;
                    if(parent -> val >= cur -> val) flag = false;
                    parent = cur;
                    cur = cur ->  right;
                }
            }
        }
        return flag;
    }
};


12.4复习：
方法1:非递归+栈+新数组
注意：用一个栈记录二叉树中序遍历的值存在一个数组中，再判断数组中是否是从小到大的顺序。
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
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode *cur = root;
        vector<int> ret;
        while(!st.empty() || cur){
            while(cur){
                st.push(cur);
                cur = cur -> left;
            }
            cur = st.top();
            st.pop();
            ret.push_back(cur -> val);
            cur = cur -> right;
        }
        for(int i = 1; i < ret.size(); ++i){
            if(ret[i] <= ret[i-1]) return false;
        }
        return true;
    }
};

方法2:递归+新数组
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
    bool isValidBST(TreeNode* root) {
        vector<int>vec;
        helper(root,vec);
        for(int i = 1; i < vec.size();++i){
            if(vec[i] <= vec[i-1]) return false;
        }
        return true;
    }
    
    void helper(TreeNode* root, vector<int>&vec){
        if(!root) return;
        helper(root -> left, vec);
        vec.push_back(root -> val);
        helper(root -> right,vec);
    }
};
方法3:递归不用新数组
在方法2的基础上进行改进，用一个flag来记录是否后面的值大于前面的值。
注意flag需要是一用引用变量，一次改变后就一直为改变后的值。
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
    TreeNode*pre = NULL;
public:
    bool isValidBST(TreeNode* root) {
        bool flag = false;
        helper(root,flag);
        if(flag) return false;
        else return true;
    }
    
    void helper(TreeNode* root, bool &flag){
        if(!root) return;
        helper(root -> left, flag);
        if(!pre){
            pre = root;
        }else{
            if(root -> val <= pre -> val) {
                flag = true;
                return;
            }
            pre = root;
        }
        helper(root -> right,flag);
    }
};
方法4:完全递归
注意用long long来写，因为如果是[2147483647]一个结点的话用int会超出范围。
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
    bool isValidBST(TreeNode* root) {
        return isvalid(root,LONG_MIN,LONG_MAX);
    }
    
    bool isvalid(TreeNode*root, long long min, long long max){
        if(!root) return true;
        if(root -> val <= min || root -> val >= max) return false;
        return isvalid(root -> left,min,root->val) && isvalid(root -> right, root -> val, max);
    }
};


2.20复习：
方法一：递归
注意：
1.需要记录下当前根结点的范围，左子树上的所有结点的值都必须小于根结点，右子树上的所有结点都必须大于根结点，因此需要记录下根结点的范围再进行递归。
2.因为会存在INT_MAX单独存在的情况，因此需要用long long的形式。
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
    bool isValidBST(TreeNode* root) {
        return isvalid(root,LONG_MIN,LONG_MAX);
   }
    
    bool isvalid(TreeNode*root, long long min, long long max){
        if(!root) return true;
        if(root->val <= min || root-> val >= max) return false;
        return isvalid(root->left, min,root->val) && isvalid(root->right,root->val,max);
    }
};

方法2:递归
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
    bool isValidBST(TreeNode* root) {
        vector<int>vec;
        helper(root,vec);
        for(int i = 1; i < vec.size();++i){
            if(vec[i] <= vec[i-1]) return false;
        }
        return true;
    }
    
    void helper(TreeNode*root, vector<int>&vec){
        if(!root) return;
        helper(root->left,vec);
        vec.push_back(root->val);
        helper(root->right,vec);
    }
};

方法3:遍历
注意
1.中序遍历需要用一个临时指针来依次走树上的结点，利用栈后进先出的性质，把左子树都入栈，没有左侧结点了出栈，入结果数组，判断右子树。
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
    bool isValidBST(TreeNode* root) {
        TreeNode *cur = root;
        vector<int>vec;
        stack<TreeNode*> st;
        while(!st.empty() || cur){
            while(cur){
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top();
            st.pop();
            vec.push_back(cur->val);
            cur = cur->right;
        }
        for(int i = 1; i < vec.size(); ++i){
            if(vec[i] <= vec[i-1]) return false;
        }
        return true;
    }
};

3.25复习
注意：中序遍历的遍历做法，用stack,需要单独建立一个树指针
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
    bool isValidBST(TreeNode* root) {
        TreeNode *p = root;
        vector<int>vec;
        stack<TreeNode*> st;
        while(!st.empty() || p){
            while(p){
                st.push(p);
                p = p -> left;
            }
            p = st.top();
            st.pop();
            vec.push_back(p -> val);
            p = p->right;
        }
        
        for(int i = 1; i < vec.size(); ++i){
            if(vec[i] <= vec[i-1]) return false;
        }
        return true;
    }

完全递归：
注意：
1.注意判断false的条件
2.因为有可能为INT_MAX一个结点，如果按照比较回返回false,实际上应该返回true,所以要更改为LONG_MIX
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
    bool isValidBST(TreeNode* root) {
        if(!root) return true;
        return helper(root,LONG_MIN,LONG_MAX);
    }
    
    bool helper(TreeNode*root, long long l, long long r){
        if(!root) return true;
        if(root-> val >= r || root-> val <= l) return false;
        return helper(root->left, l, root->val) && helper(root->right,root->val,r);
    }
};
};
