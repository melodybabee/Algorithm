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

2.3 复习
DFS
思路：
1.按照列进行输出的时候需要给每个位置增加一个标记表示列，但是题目中要求相同位置的按照从左到右排列，同一列的按照从上到下进行排序，因此就还需要记录下来行的位置。
2.那么在map中的形式就是包括pair对的vector.
vector中放入pair需要前期声明出来，写成typedef pair<int,int> p;
3.遍历map中的key,记录每一个value中的vector,对每一个vector根据高度进行排序，需要自定义排序写法
4.排序后再把数组中的第一个值输出到结果数组中
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
typedef pair<int,int> p;

class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        map<int,vector<p>>m;
        vector<vector<int>>ret;
        if(!root) return ret;
        helper(root,0,0,m);
        for(auto it: m){
            vector<p>v = it.second;
            sort(v.begin(),v.end(),[](p& v1, p& v2){
                return v1.second < v2.second;
            });
            vector<int>temp;
            for(auto num : v){
                temp.push_back(num.first);
            }
            ret.push_back(temp);
        }
        return ret;
    }
    
    void helper(TreeNode* root, int w, int h, map<int,vector<p>>&m){
        m[w].push_back({root->val,h});
        if(root->left)helper(root->left,w-1,h+1,m);
        if(root->right)helper(root->right,w+1,h+1,m);
    }
};

BFS
注意：
1.需要一个pair来记录层数，map的key表示层数，value是以层数为基础的返回数组
2.queue中需要放入一个pair,pair中要存每个结点的结点值和层数信息
3.要注意区分树的左右要用指针形式，树的值要需要用指针形式。但是pair的操作用.first和.second
需要每次取到的都是什么元素什么值
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
        map<int,vector<int>>m;
        vector<vector<int>>ans;
        if(!root) return ans;
        queue<pair<TreeNode*,int>>q;
        q.push({root,0});
        while(!q.empty()){
            auto temp = q.front();
            q.pop();
            m[temp.second].push_back(temp.first -> val);
            if(temp.first->left) q.push({temp.first->left,temp.second-1});
            if(temp.first->right)q.push({temp.first->right,temp.second+1});
        }
        for(auto it : m){
            ans.push_back(it.second);
        }
        return ans;
    }
};