题意：
把一个二叉搜索树转换成双向链表。
方法一：递归+中序遍历
思路：
1.首先题目中是二叉搜索树，二叉搜索树的性质是左<中<右，因此利用中序遍历能更好的应用这个性质。
2.通过观察例子也发现链表的顺序和中序遍历二叉树的顺序一致，因此使用中序遍历。
3.在中序遍历的过程中，先左子树遍历，再链接根结点，再遍历右子树。注意因为要生成双向链表，因此需要一个头结点来记录初始位置，还需要cur结点记录遍历到的位置。
4.因为Node结点中已经有left和right两个指针，因此每次双向连接吗，最后把头结点和cur结点连接起来即可。
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root) return NULL;
        Node *head = NULL;
        Node *cur = NULL;
        inorder(root, head,cur);
        head -> left = cur;
        cur -> right = head;
        return head;
    }
    void inorder(Node*root, Node* & head, Node* & cur){
        if(!root) return;
        inorder(root -> left, head,cur);
        if(!head){
            head = root;
            cur = root;
        }else{
            cur -> right = root;
            root -> left = cur;
            cur = root;
        }
        inorder(root -> right, head, cur);
    } 
};
方法二：非递归中序遍历
思路：
1.用一个stack写中序遍历的模版，在处理值的时候设置一个head作为链表头部，pre作为循环指针依次遍历，双向连接。
2.最后把pre和head连接起来即可。
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root) return NULL;
        Node* p = root;
        Node *head = NULL;
        Node *pre = NULL;
        stack<Node*> st;
        while(p || !st.empty()){
            while(p){
                st.push(p);
                p = p->left;
            }
            p = st.top();
            st.pop();
            if(!head) head = p;
            if(pre){
                pre -> right = p;
                p -> left = pre;
            }
            pre = p;
            p = p -> right;
        }
        head -> left = pre;
        pre -> right= head;
        return head;
    }
};
方法三：divide and conquer【需要复习】
思路：
1.跟归并排序的思想类似，首先把树拆分为各个结点，拆成每个子问题去处理。
2.对左右子树进行递归，得到了两个各自循环的双向链表，再把根结点与左右子结点断开，使左右指针都指向自己，形成单个结点。
3.再按照（左+中）+ 右的顺序拼接起来，注意尾指针的声明是头结点的左指针。
4.依次连接即可。
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root)return NULL;
        Node*left = treeToDoublyList(root -> left);
        Node*right = treeToDoublyList(root -> right);
        root -> left = root;
        root -> right = root;
        return connect(connect(left, root), right);
    }
    Node* connect(Node*node1, Node*node2){
        if(!node1) return node2;
        if(!node2) return node1;
        Node *tail1 = node1 -> left;
        Node *tail2 = node2 -> left;
        tail1 -> right = node2;
        node2 -> left = tail1;
        tail2 -> right = node1;
        node1 -> left = tail2;
        return node1;
    }
};