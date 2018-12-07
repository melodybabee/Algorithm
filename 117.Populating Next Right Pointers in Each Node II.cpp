题意：
116 follow up,但是不是完美二叉树
方法一：queue+for循环
思路：
解法和116一模一样，这种做法因为没有用到完美二叉树的性质，因此在此题中仍然适用。但是不满足空间复杂度为线性的要求。
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
        queue<TreeLinkNode*>q;
        q.push(root);
        while(!q.empty()){
            int size = q.size();
            for(int i = 0; i < size;++i){
                TreeLinkNode *temp = q.front();
                q.pop();
                if(i < size-1) temp -> next = q.front();
                if(temp -> left) q.push(temp -> left);
                if(temp -> right)q.push(temp -> right);
            }
        }
    }
};
方法2:设置dummy结点进行遍历，线性空间复杂度
思路：
1.首先设置一个dummy结点用来记录每一行的起始位置为了便于循环完一行之后知道下一行作为root的结点在哪里。
2.设置一个cur指针用来遍历每一行，当根左存在时，cur更新到根左的位置，如果根右存在，那么继续移动到根右，同时连接next指针。
3.每当遍历完一个结点，判断结点的next是否存在，如果存在，继续遍历root->next结点，注意此时cur是连着上面的状态的，不会更新下一行的新的根结点。
4.如果next不存在，那么cur回到dummy结点，根结点等于dummy的next,同时注意把dummy断开。
注意如果不断开的话那么到了叶子结点就会形成死循环为TLE。
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
        TreeLinkNode *dummy = new TreeLinkNode(-1);
        TreeLinkNode *cur = dummy;
        while(root){
            if(root -> left){
                cur -> next = root->left;
                cur = cur -> next;
            }
            if(root -> right){
                cur -> next = root -> right;
                cur = cur -> next;
            }
            root = root -> next;
            if(!root){
                cur = dummy;
                root = cur -> next;
                dummy -> next = NULL;
            }
        }
    }
};