题意：序列化和解序列化树
方法一：BFS
思路：
1.序列化就是将一个数据结构或物体转化为一个位序列，可以存进一个文件或者内存缓冲器中。
然后通过网络连接在相同的或者另一个电脑环境中被还原，还原的过程叫做去序列化。
2.序列化的结果是一个输出，因此需要创建输出字符串流iostringstream
每次输入新的值或者输入空结点或者最后输出的时候都需要用字符串流out来操作。
3.序列化要用到输入，因此要创建一个输入流in,用in来读取每次要输入的值，树结点是数值，in读入的是字符，所以还要stoi(val)操作
4.建树过程同样需要栈，每次根结点入栈，在循环中取出，如果不存在输入流那么break
如果存在输入流且不是#，分别建左子树和右子树，同时把根结点入栈
5.最后返回跟结点
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode*>q;
        ostringstream out;
        if(root) q.push(root);
        while(!q.empty()){
            TreeNode *t = q.front();
            q.pop();
            if(t){
                out << t -> val << ' ';
                q.push(t->left);
                q.push(t->right);
            }else{
                out << "# ";
            }
        }
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.empty()) return NULL;
        istringstream in(data);
        queue<TreeNode*>q;
        string val;
        in >> val;
        TreeNode *root = new TreeNode(stoi(val));
        TreeNode *cur = root;
        q.push(cur);
        while(!q.empty()){
            TreeNode *t = q.front();
            q.pop();
            if(!(in >> val)) break;
            if(val != "#"){
                cur = new TreeNode(stoi(val));
                q.push(cur);
                t->left = cur;
            }
            if(!(in >> val)) break;
            if(val != "#"){
                cur = new TreeNode(stoi(val));
                q.push(cur);
                t->right = cur;
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

方法2:先序遍历
思路：
1.序列化的时候如果有根输出根的值，递归调用左子树和右子树，不存在根就返回#
2.去序列化的时候如果读取的为#，那么返回NULL，每次创建新的根结点，再用根左和根右调用递归形成新的子树，最后返回根结点
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
private:
    void serialize(TreeNode *root,ostringstream &out){
        if(root){
            out << root -> val << ' ';
            serialize(root -> left,out);
            serialize(root -> right, out);
        }else{
            out << "# ";
        }
    }
    
    TreeNode* deserialize(istringstream &in){
        string val;
        in >> val;
        if(val == "#") return NULL;
        TreeNode*root = new TreeNode(stoi(val));
        root -> left = deserialize(in);
        root -> right = deserialize(in);
        return root;
    }
    
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root,out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));