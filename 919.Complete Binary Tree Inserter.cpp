题意：完全二叉树的遍历
思路：
1.题目要求构建一个完全二叉树，并不断插入新的元素，新插入的元素需要返回父结点，最后还要能返回整棵树
2.那么在建树阶段需要建立一个队列，这样便于遍历，同时方便表示父结点的位置
3.进入插入方法后，设置一个树指针为空，只要这个指针为空，就一直进入while循环中进行查找
首先判断队列中头部结点的左结点是否存在，不存在的话当前根结点为父结点，在其左侧插入新的值即可
如果左结点存在判断右结点是否存在，不存在的话操作同上
如果左右都存在，说明以这个根为结点的树是完全二叉树，那么就对其左右进行入队列操作，再次进行查找，最后返回父结点的值。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class CBTInserter {
private:
    TreeNode *node;
    queue<TreeNode*>q;
public:
    CBTInserter(TreeNode* root) {
        node = root;
        q.push(node);
    }
    
    int insert(int v) {
        TreeNode *ret = NULL;
        while(!ret){
            TreeNode *temp = q.front();
            if(!temp -> left){
                ret = temp;
                temp -> left = new TreeNode(v);
            }else if(!temp -> right){
                ret = temp;
                temp -> right = new TreeNode(v);
            }else{
                q.pop();
                q.push(temp->left);
                q.push(temp->right);
            }
        }
        return ret->val;
    }
    
    
    TreeNode* get_root() {
        return node;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */