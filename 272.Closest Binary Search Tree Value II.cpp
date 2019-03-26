题意：270变形，找到最接近目标值的k的元素
方法一：中序遍历+找到范围+依次push
思路：
1.首先根据BST的性质建立一个中序遍历的数组
2.找到最接近目标值的距离和位置，记录下来，左边界-1，右边界+1
3.每次push进去一个新的元素，再根据左右的差别判断向左移动还是向右移动，注意要区分边界，如果越界了就一直向一个方向移动
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
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int>ret;
        vector<int>inorder;
        helper(inorder,root);
        double diff = (double)INT_MAX;
        int index = 0;
        for(int i = 0; i < inorder.size(); ++i){
            if(diff >= abs(target-inorder[i])){
                diff = abs(target-inorder[i]);
                index = i;
            }
        }
        int l = index -1;
        int r = index +1;
        while(ret.size() < k){
            ret.push_back(inorder[index]);
            if(l >= 0 && r < inorder.size()){
                if(abs(target-inorder[l]) >= abs(target-inorder[r])){
                    index = r;
                    ++r;
                }else{
                    index = l;
                    --l;
                }
            }else if(l >= 0){
                index = l;
                --l;
            }else{
                index = r;
                ++r;
            }
        }
        return ret;
    }
    
    void helper(vector<int>&inorder,TreeNode* root){
        if(!root) return;
        helper(inorder,root->left);
        inorder.push_back(root->val);
        helper(inorder,root->right);
    }
};
优化：
在中序遍历的过程中进行比较
思路：
1.在遍历的过程中不断push进去新的元素，如果超过了指定的k的大小，那么比较，从头部开始弹出
利用了所有返回的结果都会是连续的性质
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
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> ret;
        helper(ret, root, target, k);
        return ret;
    }
    
    void helper(vector<int>&ret, TreeNode*root, double target, int k){
        if(!root) return;
        helper(ret, root->left, target, k);
        if(ret.size() < k) ret.push_back(root->val);
        else if(abs(target-ret[0]) > abs(target-root->val)){
            ret.erase(ret.begin());
            ret.push_back(root->val);
        }else return;
        helper(ret, root->right,target,k);
    }
};

遍历方法：
注意：
1.中序遍历需要用到stack来存在找到最左侧结点前的所有结点，到头之后直接用当前的指针指向stack的弹出的元素
2.如果小于规定的大小，直接push进去，否则进行比较，如果有一个元素不满足比较了，那么直接结束判断
3.在中序遍历过程中最后指针指向右结点
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
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> ret;
        stack<TreeNode*> st;
        TreeNode *p = root;
        while(!st.empty() || p){
            while(p){
                st.push(p);
                p = p -> left;
            }
            p = st.top();
            st.pop();
            if(ret.size() < k) ret.push_back(p->val);
            else if (abs(target-ret[0]) > abs(target-p->val)){
                ret.erase(ret.begin());
                ret.push_back(p->val);
            }else{
                break;
            }
            p = p -> right;
        }
        return ret;
    }
};

方法二：最大栈
思路：
1.维护一个最大栈，用一对pair表示距离和根的值，根据距离排序
2.中序遍历，每次输入这一对属性，如果栈的大小超过k,开始从头部弹出。因为c++维护的是最大栈，所以最后留下的都是距离较近的元素。
3.再把priority_queue里面的元素输出即可。注意弹出。
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
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> vec;
        priority_queue<pair<double,int>>q;
        helper(target,root,q,k);
        while(!q.empty()){
            vec.push_back(q.top().second);
            q.pop();
        }
        return vec;
    }
    
    void helper(double target, TreeNode* root, priority_queue<pair<double,int>>&q, int k){
        if(!root) return;
        helper(target,root->left,q,k);
        q.push({abs(target-root->val),root->val});
        if(q.size() > k) q.pop();
        helper(target,root->right,q,k);
    }
};