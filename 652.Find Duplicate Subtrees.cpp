题意：找到树中所有重复的子树，返回子树的根结点
思路：
1.因为需要遍历树才能知道是否有重复的子树，那么就需要一个map来记录遍历的结果和对应的结点
用set也可以记录，但是set无法计数。题目中的要求是如果有多个重复的就返回一个，那么就是map中的value值为1的时候返回，如果有更多只返回一个但不影响累加。
set每次重复都会再次返回。
2.对树进行后序遍历，即左右中的遍历。
从根结点开始，记录下值之后对其左右子树调用递归，最后返回为一个后序遍历的序列。每个序列在map中作为key,value在序列中作为计数。
3.只要在map中查找到了当前序列，说明之前出现过，那么就是重复的子树，返回当前树的根结点在结果数组中。
注意：
1.在行程序列的过程中，转换为string类型更为直观。如果不存在根就是#,在每个结点之间用,分隔开
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
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        vector<TreeNode*>ans;
        unordered_map<string,int>map;
        helper(ans,map,root);
        return ans;
    }
    
    string helper(vector<TreeNode*>&ans,unordered_map<string,int>&map,TreeNode* root){
        if(!root) return "#";
        string temp = to_string(root->val) + "," + helper(ans,map,root->left) + "," + helper(ans,map,root->right);
        if(map[temp] == 1) ans.push_back(root);
        ++map[temp];
        return temp;
    }
};