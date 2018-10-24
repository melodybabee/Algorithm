题意：
层序遍历，把同一行的每一的结点加一个指针指向该层的下一个结点，如果没有，指向NULL
方法一：用queue进行遍历，用null作为层数的标志
思路：
1.设置一个栈，先把根结点push进去，每一层用NULL隔开
2.每次读取栈的第一个元素，pop()出来，如果第一个元素存在，把它的next指向栈此时的头结点，如果不存在，判断是否栈为空，若为空，return,否则在末尾push进去新的NULL分层
3.在操作完头结点的next之后，如果头结点的左子树存在，push进栈，如果头结点的右子树存在，push进栈
注意：
queue操作头结点是q.front();弹出第一个元素是q.pop();
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        queue<TreeLinkNode*> q;
        q.push(root);
        q.push(NULL);
        while(true){
            TreeLinkNode* cur = q.front();
            q.pop();
            if(cur){
                cur-> next = q.front();
                if(cur -> left) q.push(cur -> left);
                if(cur -> right) q.push(cur -> right);
            }else{
                if(q.size() == 0) return;
                q.push(NULL);
            }
        }
    }
};
方法2:递归
思路：
1.首先判断根结点是否存在，不存在直接返回
2.因为题目中给出了是完全二叉树，因此如果左结点存在，那么右结点一定存在，因此左结点的next直接指向根结点的右结点即可
3.如果根结点的右结点存在，需要判断根结点的next是否存在，如果不存在，那么根结点的右结点也指向null
如果根结点的next不是空，那么根结点的右结点的next指向根结点的next的左结点
4.再递归根左和根右即可
注意：
1.注意看清楚题目中给出的已知条件，因为是完全二叉树，所以如果有左结点那么一定有右结点
2.还说明了在初始状态下all next pointers are set to NULL，因此第一行的根结点已经指向了NULL，不需要再次指向
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        if(root -> left) root -> left -> next = root -> right;
        if(root -> right){
            if(!root -> next) root -> right -> next = NULL;
            else root -> right -> next = root ->next -> left;
        }
        connect(root -> left);
        connect(root -> right);
    }
};
方法3:用queue进行遍历，for循环
思路：
1，和第一种方法的思路一样，都是BFS层次遍历的思路。但是注意在for循环输出的时候，i要停在size的前一位。本题中已经给所有结点初始的next为空了。
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        queue<TreeLinkNode*> q;
        q.push(root);
        while(!q.empty()){
            int size = q.size();
            for(int i = 0; i < size;++i){
                TreeLinkNode *tre = q.front();
                q.pop();
                if(i < size-1) tre -> next = q.front();
                if(tre -> left) q.push(tre -> left);
                if(tre -> right) q.push(tre -> right);
            }
        }
    }
};
方法4:S(n) = O(1)
思路：
1.用start来记录每一层的起始位置，cur用来遍历每一层，思路和第二种类似
2.如果当前结点存在，当前的左的next等于当前的右
如果当前的next存在，当前的右的next等于当前的next的左，当前结点向右移动
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        TreeLinkNode*start = root;
        TreeLinkNode*cur = NULL;
        while(start -> left){
            cur = start;
            while(cur){
                cur -> left -> next = cur -> right;
                if(cur -> next) cur -> right -> next = cur -> next -> left;
                cur = cur -> next;
            }
            start = start -> left;
        }
    }
};