题意：判断一棵树是否是另一棵树的子树
方法一：递归
思路：
1.找到两颗树相同的根结点后开始判断是否是相同的树，分别再对标准树的左子树与右子树进行递归
2.在判断两棵树的方法中，当左右都不存在的时候返回true,如果一个存在或者值不等的时候返回false
再对两棵树分别进行左子树递归和右子树递归
注意：
1.因为只要有一种情况满足条件就返回true,所以check(s,t)是写在if判断条件里面的，如果不满足的话会直接跳过程序继续进行
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
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(!s) return false;
        if(check(s,t)) return true;
        else return isSubtree(s -> left,t) || isSubtree(s -> right,t);
    }
    
    bool check(TreeNode* s, TreeNode* t){
        if(!s && !t) return true;
        if(!s || !t) return false;
        if(s -> val != t -> val) return false;
        return check(s->left, t -> left) && check(s -> right, t->right);
    }
};
方法2:序列化
思路：
1.用ostringstream来表示字符串的输出，分别对两个字符串进行序列化，判断第二个是否是第一个的子串
2.如果到结尾的话就加上#，否则每个数字用，隔开
3.os<< 表示引入新的值，os.str()表示输出成字符串的形式
4.npos is a static member constant value with the greatest possible value for an element of type size_t.
npos在string中表示in string's member functions, means "until the end of the string".字符串的结尾
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
    bool isSubtree(TreeNode* s, TreeNode* t) {
        ostringstream os1;
        ostringstream os2;
        serialize(s,os1);
        serialize(t,os2);
        return os1.str().find(os2.str()) != string::npos;
    }
    
    void serialize(TreeNode* s,ostringstream &os){
        if(!s) os << '#';
        else{
            os << ',' << s -> val;https://blog.csdn.net/JIEJINQUANIL/article/details/51789682
            serialize(s -> left,os);
            serialize(s -> right,os);
        }
    }
};
补充：
istringstream类用于执行C++风格的串流的输入操作。 
ostringstream类用于执行C风格的串流的输出操作。 
strstream类同时可以支持C风格的串流的输入输出操作。
在输出的时候需要用.str()方法表示输出的字符串