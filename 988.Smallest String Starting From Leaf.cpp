题意：输出二叉树中最小的字母路径，如果相等按照字典序排列
思路：
1.对树进行DFS遍历，即用DFS递归方法依次输出每一条路径，在输出的同时也进行比较
2.首先如果不存在根结点，那么返回空，分别记录下当前结点中的左子树字符串和右子树字符串，用一个新建的变量作为每次遍历的临时变量。
新建的变量等于当前的字符串再加上每次遍历后新加入的字符。
3.如果左右都不存在，那么返回空；如果左右其中一边不存在，那么返回存在的另一侧；如果都存在，返回较小的一侧
4.因为原树中是数值的形式，需要转换成字符，利用ASCII码相加的方式，需要转换(char)类型
补充：
1.ASCII码转换
char c='1';
int a=(int) c;//此时的结果是把字符c转换为int形式，那么将得到字符'1'的ASCII码；
int a=c-48;或者int a=c-'0';//int = char - char直接对c进行ASCII码相减，1的ASCII码是49，49-48=1，将得到数字1；字符0的ascii值是48
2.常见ASCII码
int ASCII 
符号 0-48
0   48
A   65
a   97
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
    string smallestFromLeaf(TreeNode* root) {
        if(!root) return"";
        string l = smallestFromLeaf(root->left);
        string r = smallestFromLeaf(root -> right);
        string ret;
        if(l == "" && r == ""){
            ret += (root->val + 'a');
        }else if(l == "" ){
            ret += r + (char)(root->val + 'a');
        }else if(r == "" ){
            ret += l + (char)(root -> val + 'a');
        }else if(l < r){
            ret += l + (char)(root -> val + 'a');
        }else{
            ret += r + (char)(root->val + 'a');
        }
        return ret;
    }
};