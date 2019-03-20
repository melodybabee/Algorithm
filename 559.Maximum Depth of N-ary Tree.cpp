题意：
找到普通的树中的最深的深度
思路：
1.用一个ret来记录结果。注意要和level进行区分,level负责记录递归到哪一层了。
2.DFS递归不断查找，最后返回ret中的较大值作为结果。
注意：
1.因为只有一个结点的时候返回值需要是1，因此level和ret的初始值都为1，这样就需要单独处理空结点的情况。
/*
// Definition for a Node.
class Node {
public:
    int val;
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
    int maxDepth(Node* root) {
        if(!root) return 0;
        int level = 1;
        int ret = 1;
        helper(ret,level,root);
        return ret;
    }
    
    void helper(int &ret,int level, Node *root){
        if(!root) return;
        for(auto c : root->children){
            ret = max(ret,level+1);
            helper(ret,level+1, c);
        }
    }
};

优化：
1.在遍历子结点的过程中不断进行递归，每次的层数+1，需要一个值来记录“较大”的结果。
/*
// Definition for a Node.
class Node {
public:
    int val;
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
    int maxDepth(Node* root) {
        if(!root) return 0;
        int res = 1;
        for(auto c : root->children){
            res = max(res, maxDepth(c)+1);
        }
        return res;
    }
};