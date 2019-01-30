题意：找到BST中出现次数最多的元素
方法一：DFS遍历
思路：
1.因为需要找到的是出现次数最多的元素，那么就需要map来记录每个数字出现的次数
2.BST最简单的就是通过中序遍历来进行计数，记录过程中出现的最多的数量
3.再遍历一次map,如果出现的次数等于最大次，那么输入结果数组中
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
    vector<int> findMode(TreeNode* root) {
        unordered_map<int,int>map;
        int mx = 0;
        vector<int>ans;
        helper(root,map,mx);
        for(auto m : map){
            if(m.second == mx){
                ans.push_back(m.first);
            }
        }
        return ans;
    }
    void helper(TreeNode* root,unordered_map<int,int>&map,int &mx){
        if(!root) return;
        helper(root->left,map,mx);
        mx = max(mx,++map[root->val]);
        helper(root->right,map,mx);
    }
};
方法2：优化空间复杂度
思路：
1.上面的方法中因为哈希表占用了空间，那么就用其他方法来替代哈希表的功能即可
2.利用BST中序遍历会按顺序出现的性质，需要mx来记录出现的最大值，count来记录当前的个数，pre表示之前一位结点的数值
3.在到根结点之后，如果前一位pre存在，那么比较是否相同，相同的话++count,不同的话就为1
比较当前的计数是否大于等于mx，如果大于把数组清空放入新的数字，如果等于那么直接放入新的数字即可
4.更新pre指针的位置
5.最后返回结果数组
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
    vector<int> findMode(TreeNode* root) {
        int mx = 0;
        vector<int>ans;
        TreeNode* pre = NULL;
        int count = 1;
        helper(root,ans,mx,pre,count);
        return ans;
    }
    void helper(TreeNode* root,vector<int>& ans,int& mx, TreeNode* &pre, int& count){
        if(!root) return;
        helper(root->left,ans,mx,pre, count);
        if(pre){
            count = (root -> val == pre -> val) ? ++count : 1;
        }
        if(count >= mx){
            if(count > mx) ans.clear();
            ans.push_back(root -> val);
            mx = count;
        }
        pre = root;
        helper(root->right,ans,mx,pre,count);
    }
};