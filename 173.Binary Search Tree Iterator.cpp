题意：
设计一个程序实现二叉搜索树能每次返回当前最小的值。
思路：
1.首先建立一个栈，因为二叉搜索树的中序遍历能够满足从小到大输出的性质，BST左<中<右的性质。
因此需要把大的值先入栈，小的值后入栈，后进先出。
2.从根结点开始向左依次入栈，直到左子树的左叶子结点。
3.当栈为空的时候，表示二叉树已经遍历完毕，没有后面的值了。
4.每当要求输出当前最小值的时候，栈顶元素就是最小值，返回即可。
但是需要注意有可能栈顶元素还有右子树，及右子树的左子树，所以需要判断，如果有右子树，那么入栈，如果右子树还有左子树，入栈，直到把右子树的最左边一个叶子结点入栈，为当前的最小值。
注意：
1.C++也是面向对象编程，首先需要建立一个全局变量使得所有方法都可以调用这个值，即属性。
2.定义结构体之后可以直接操作已经声明好的结构。
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator { 
private:
    stack<TreeNode*> st;
public:
    BSTIterator(TreeNode *root) {
        while(root){
            st.push(root);
            root = root -> left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(st.empty()) return false;
        else return true;
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *min = st.top();
        int ret= min -> val;
        st.pop();
        if(min -> right){
            min = min -> right;
            while(min){
                st.push(min);
                min = min -> left;
            }
        }
        return ret;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */