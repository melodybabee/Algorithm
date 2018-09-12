/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //非递归做法
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<int> v;
        vector<vector<int>> ans;
        queue<TreeNode*> que;
        
        if(!root) return ans;
        que.push(root);
        que.push(NULL);
        
        while(!que.empty()){
            TreeNode* p = que.front();
            que.pop();
            if(p == NULL){
                if(v.empty()) break;
                else{
                    que.push(NULL);
                    ans.insert(ans.begin(),v);
                    v.clear();
                    continue;
                }
            }
            else{
                v.push_back(p -> val);
            }
            if(p -> left)
                que.push(p -> left);
            if(p -> right)      
                que.push(p -> right);
        }
        return ans;   
    }
};
/*
思路：
1.首先判断根是否存在，存在的话存入queue
2.设定指针指向queue的第一个位置，将其的值push到每一个vector子集中
3.再将p的左子结点和右子结点分别输出到queue结尾
4.如果指针遇到NULL元素，判断此时进行的状态（等待输出还是已经到结尾），将子vector输出在父vector中

难点：
1.本题难点在于如何划分树的每一层，从而把他们放在一个子vector中，方法是在每一层最后加一个NULL入队列
如果指针在queue中读取到了NULL，先判断子vector中是否有元素
有的话将这个vector从头部插入到vector ans中，同时清空子vector
如果没有，即表示已经到结尾，直接break即可

注意：
1.vector从头部插入的方法，vector.insert(vector.begin(),要插入的元素值)
2.清空vector,vector.clear()
*/
//递归做法
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector <vector<int>> ret;
        if(!root) return ret;
        levelOrder(root,0,ret);
        reverse(ret.begin(),ret.end());
        return ret;
        
    }
    void levelOrder(TreeNode* root, int level, vector<vector<int>> &ret){
        if(ret.size()==level) ret.push_back({});
        ret[level].push_back(root -> val);
        if(root -> left) 
            levelOrder(root -> left, level+1, ret);
        if(root -> right) 
            levelOrder(root -> right, level+1, ret);
        }
};
/*
思路：
1.分析题目，要求是将每行输出到vector中，因此需要将树的每层从第一个元素开始，输出到子vector中，即可解决问题
2.因此所需要的变量有root,层数（对应了父vector中哪一个子vector),需要输出的父vector
3.当ret的大小与level相等时，即有新的子vector加入，要引入{}
4.以此类推，插入顺序是前序遍历的顺序，对应子vector非顺序插入）
注意：
1.vector的reverse方法,reverse(vector.begin(),vector.end());可实现反转
代码：【需要再看】
template <class BidirectionalIterator> void reverse (BidirectionalIterator first, BidirectionalIterator last)
{
     while ((first!=last)&&(first!=--last))
     {
          std::iter_swap (first,last);//交换first and last
          ++first;
     }
}
2.void不需要return,其余需要按照类型return
【问题】如果代码写成了，在返回levelOrder的时候加了return,输出是{{9}{3}},不清楚原因
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector <vector<int>> ret;
        if(!root) return ret;
        levelOrder(root,0,ret);
        reverse(ret.begin(),ret.end());
        return ret;
        
    }
    void levelOrder(TreeNode* root, int level, vector<vector<int>> &ret){
        if(ret.size()==level) ret.push_back({});
        ret[level].push_back(root -> val);
        if(root -> left) 
            return levelOrder(root -> left, level+1, ret);
        if(root -> right) 
            return levelOrder(root -> right, level+1, ret);
        }
};

*/
