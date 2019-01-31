题意：找到二叉树中距离目标结点长度为K的所有结点的值
思路：DFS
1.主要思路是以目标结点为中心，向它的四周进行扩散，扩散到距离目标结点为K的位置即可。
2.找一个结点的左右子结点比较容易，而对于他的parent结点，需要建立一个map记录下来
3.所以首先建立一个map,key放入树的每个结点，value部分放入它的父结点，用DFS把树的所有结点关系对应，因为每个结点都不相同，所以unordered_map就可以应用
4.进行DFS遍历，如果K等于0的时候，在结果数组中插入目标值。
如果不等于0，那么判断左右子结点以及map中的父结点是否存在，进行DFS递归。
注意：
1.因为需要判断左右子结点和父结点，避免重复判断一个相同的数字，需要用一个set来记录下是否判断过某个结点，判断过直接return,没有的话在set中insert这个结点。
2.在判断的时候也可以以目标结点结合queue来进行BFS判断，首先把结点放入queue,在进入BFD进行记录下一层的个数，如果K>0再分别让左右子结点和父结点入队列
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
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        unordered_map<TreeNode*,TreeNode*>map;
        vector<int>vec;
        set<TreeNode*>visited;
        findroot(root,map);
        dfs(target,K,vec,map,visited);
        return vec;
    }
    void dfs(TreeNode* t, int k, vector<int>&vec,unordered_map<TreeNode*,TreeNode*>&map,set<TreeNode*>&visited){
        if(visited.find(t) != visited.end()) return;
        visited.insert(t);
        if(k == 0){
            vec.push_back(t->val);
            return;
        }
        if(t -> left){
            dfs(t->left,k-1,vec,map,visited);
        }
        if(t -> right){
            dfs(t->right,k-1,vec,map,visited);
        }
        TreeNode* p = map[t];
        if(p){
            dfs(p,k-1,vec,map,visited);
        }
    }
    void findroot(TreeNode* root,unordered_map<TreeNode*,TreeNode*>&map){
        if(!root) return;
        if(root->left){
            map[root->left] = root;
            findroot(root->left,map);
        }
        if(root->right){
            map[root->right] = root;
            findroot(root->right,map);
        }
        return;
    }
};