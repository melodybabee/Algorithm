题意：二叉树的竖直遍历
思路：
1.因为输出类似于层序遍历，所以在层序遍历的基础上进行加工。
只要向左走，那么就给根结点的编号-1，如果向右走，那么就在根结点的基础上+1
2.设置一个map，用来存储编号和根结点的值的vector的映射。用map是因为是有序的，而直接放入值便于最后的输出。
3.同时建立一个pair对放入层序遍历的queue中，因为要不断更新编号。
进入while层序遍历之后，开始提取栈顶元素，注意queue是q.front(),在map中放入值。
如果左结点存在，以pair形式存入，右结点同理。
4.最后从map中依次将vector输出到返回数组中。
5.注意判断根结点是否存在的问题。
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
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if(!root) return ret;
        map<int,vector<int>>map;
        queue<pair<TreeNode*,int>>q;
        q.push({root,0});
        while(!q.empty()){
            auto it = q.front();
            q.pop();
            map[it.second].push_back(it.first -> val);
            if(it.first->left)  q.push({it.first->left,it.second-1});
            if(it.first->right)  q.push({it.first->right,it.second+1});
        }
        for(auto m :map){
            ret.push_back(m.second);
        }
        return ret;
    }
};