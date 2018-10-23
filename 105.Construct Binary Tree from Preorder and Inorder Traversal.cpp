题意：
给出一个树的前序遍历和中序遍历，找到这棵树
思路：
1.前序遍历的第一个结点就是这棵树的根，那么从中序遍历的数组中找到这个结点，就可以知道左子树结点集和右子树结点集
2.这样的话跟的左子树的根结点就是前序遍历中的第二个结点，左子树的最后一个结点就是前序遍历中对应中序遍历的根结点位置。
右子树的根结点就是在前序遍历的数组中，对应中序遍历根结点位置的下一位，右子树最后一位是前序遍历中的最后一位，以此递归。
举例：
Preorder:　  　5　　4　　11　　8　　13　　9
Inorder:　　 　11　　4　　5　　13　　8　　9
step1:
5　　4　　11　|　8　　13　　9　　　　　　=>　　　　　　　　　  5
11　　4　　5　|　13　　8　　9　　　　　　　　　　　　　　　　/　　\
step2:
4　　11　 |　　8　　 13　 9　　　　　　=>　　　　　　　　 5
11　 4　　|　 13　　 8　　9　　 　　　　　　　　　　　　/　　\
　　　　　　　　　　　　　　　　　　　　　　　　　　　　 4　　　8
step3:
1　　　　 　　13　　　　9　　　　　　　　=>　　　　　　　　　5
11　　　　　　13　　　　9　　　　 　　　　　　　　　　　　 /　　\
　　　　　　　　　　　　　　　　　　　　　　　　　　　　　 4　　　8
　　　　　　　　　　　　　　　　　　　　　　　　　　　　/　　　 /     \
　　　　　　　　　　　　　　　　　　　　　　　　　　　11　　  13　　  9

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
    }
    TreeNode* build(vector<int>& preorder,int pstart,int pend,vector<int>& inorder,int istart,int iend){
        if(pstart > pend || istart > iend) return NULL;
        int i = 0;
        for(i = istart; i < iend; ++i){
            if(preorder[pstart] == inorder[i]){
                break;
            }
        }
        TreeNode *root = new TreeNode(preorder[pstart]);
        root -> left = build(preorder,pstart+1,pstart+i-istart,inorder,istart,i-1);
        root -> right = build(preorder,pstart+i+1-istart,pend,inorder,i+1,iend);
        return root;
    }
};