题意：
145 follow up,普通树的后序遍历。
方法一：递归
思路：
1.主要是巩固一下后序遍历的思路同时熟悉下非二叉树的递归和遍历，思路和二叉树的后序遍历相同。
2.从根结点开始递归，用一个for循环依次遍历根结点的孩子们，当没有孩子的时候输出当前值。
注意：
1.在调用结点的值的时候看结构体内的属性就可以，本题有val,children两个，因此可以直接root -> 调用这两个属性。
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
    vector<int> postorder(Node* root) {
        vector<int> ret;
        helper(root,ret);
        return ret;
    }
    
    void helper(Node *root, vector<int>&ret){
        if(!root) return;
        for(int i = 0; i < root -> children.size();++i){
            helper(root -> children[i], ret);
        }
        ret.push_back(root -> val);
    }
};
方法二：遍历
思路：
1.本题因为不易确认children的个数，因此后序遍历的模版不易操作。
2.通过观察题目，发现如果从根结点开始输入，再从下一层的children的尾部开始依次输出，最后反转结果数组那么就能得到正确的结果。
3.因此没遍历到根结点，输入结果数组，从头部开始在栈中输入children数组的各个结点，输出值的时候后进先出，因此会输出尾部的值。
4.最后反转结果数组。
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
    vector<int> postorder(Node* root) {
        vector<int> ret;
        if(!root) return ret;
        stack<Node*>st;
        st.push(root);
        Node *temp = NULL;
        while(!st.empty()){
            temp = st.top();
            st.pop();
            ret.push_back(temp -> val);
            if(temp -> children.empty()) continue;
            for(int i = 0; i < temp -> children.size() ;++i){
                st.push(temp -> children[i]);
            }
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }
};
