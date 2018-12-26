题意：多维树的层序遍历
思路：
1.同样用一个queue进行层序遍历，在每次进入while循环的时候统计queue中的个数，输出到数组中
2.注意此处的数组也要重新声明，或者在尾部清空，保证每次都是空的数组
3.每把结点放到新的数组中，就遍历它的children输入到queue中，最后返回结果数组
/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>>ret;
        if(!root) return ret;
        queue<Node*>q;
        q.push(root);
        while(!q.empty()){
            int temp= q.size();
            vector<int>ans;
            for(int i= 0; i < temp ;++i){
                Node *t = q.front();
                q.pop();
                ans.push_back(t->val);;
                for(int j = 0; j < t->children.size();++j){
                    q.push(t->children[j]);
                }
            }
            ret.push_back(ans);
        }
        return ret;
    }
};