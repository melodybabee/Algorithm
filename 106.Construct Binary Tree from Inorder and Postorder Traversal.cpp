题意：
根据后续遍历和中序遍历找到树（同类题目105题，根据前序遍历和中序遍历找到一棵树）
思路：
1.通过观察发现，后续遍历中的尾部元素为根结点，因此在中序遍历中找到这个元素，其左为左子树，其右为右子树
2.将上述过程递归，左子树在中序遍历中对应的位置也是其在后续遍历中的对应位置；
右子树在中序遍历中的对应的位置是在后续遍历中，左子树后面与根结点前面的位置。
举例：
Inorder:　　 　11　　4　　5　　13　　8　　9
Postorder:　　 11　　4　　13　　9　　8　　5　
step1:
11　　4　　5　　13　　8　　9　　　　　　=>　　　　　　　　　 5
11　　4　　13　　9　　8　　5　　　　　　　　　　　　　　　　/　　\　
step2:
11　　4　　 　　13　　 8　　9　　　　　　=>　　　　　　　　　5
11　　4　　　　 13　　 9　　8　　 　　　　　　　　　　　　 /　　\
　　　　　　　　　　　　　　　　　　　　　　　　　　　　　 4　　　8
step3:
11　　　　 　　13　　　　9　　　　　　　　=>　　　　　　　　　5
11　　　　　　 13　　　　9　　　　 　　　　　　　　　　　　 /　　\
　　　　　　　　　　　　　　　　　　　　　　　　　　　　　  4　　　8
　　　　　　　　　　　　　　　　　　　　　　　　　　　　/　　　 /     \
　　　　　　　　　　　　　　　　　　　　　　　　　　　 11　　  13　　  9
注意：
1.如何判断在调用递归的时候参数写的是否正确，想具体的情况举例，比如根结点就是左起始点或者右起始点的时候能否成立
2.为什么只知道前序遍历和后续遍历不能确认一棵二叉树：
比如下面五棵树：
    1　　　　　preorder:　　  1　　2　　3
   / \　　　  inorder:　　    2　　1　　3
 2    3　　   postorder:　　 2　　3　　1

       1   　 preorder:　　   1　　2　　3
      / 　　　 inorder:　　    3　　2　　1
    2 　　　　  postorder: 　　3　　2　　1
   /
 3
       1　　　　 preorder:　　  1　　2　　3
      / 　　　　 inorder:　　   2　　3　　1
    2 　　　　　 postorder:　　 3　　2　　1
      \
       3

       1　　　　   preorder:　　  1　　2　　3
         \ 　　　　inorder:　　   1　　3　　2
          2 　　　 postorder:　　3　　2　　1
         /
       3

       1　　　　     preorder:　　  1　　2　　3
         \ 　　　　　inorder:　　   1　　2　　3
          2 　　　　 postorder:　　3　　2　　1
            \
　　　　      3
从上面可以看出，对于先序遍历都为1 2 3的五棵二叉树，它们的中序遍历都不相同，而它们的后序遍历却有相同的，所以只有和中序遍历一起才能唯一的确定一棵二叉树。
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return build(inorder,0,inorder.size()-1,postorder,0,postorder.size()-1);
    }
    TreeNode *build(vector<int>& inorder, int istart,int iend, vector<int>& postorder,int pstart,int pend){
        if(istart > iend || pstart > pend) return NULL;
        int i = 0;
        TreeNode *p = new TreeNode(postorder[pend]);
        for(i = istart; i< inorder.size(); ++i){
            if(inorder[i] == p->val)
                break;
        }
        p -> left = build(inorder,istart,i-1,postorder,pstart,pstart+i-1-istart);
        p -> right = build(inorder,i+1,iend,postorder,pstart+i-istart,pend-1);
        return p;
    }
};