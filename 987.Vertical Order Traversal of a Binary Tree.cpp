题意：对树的每一列进行遍历，314follow up
思路：
1.对列进行遍历就需要记录下每一列的序号，那么利用map可以自动进行排序
2.但是本题还要求在位置相同的条件下对按照数值的大小排序，那么就还需要另一个map记录下当前的层数，如果层数靠前正常输出，如果相同那么需要对当前的数组进行排序
3.首先用DFS在map中输入每一个结点位置，包括数值，宽度和高度
4.遍历map,对map中的value进行遍历，value部分是key为高度的map,对于每一个value中的数组，进行sort排序
因为此时只是一个一个的数值了，所以需要在结果数组汇总的指定位置一个一个输入数组中的值
5.最后返回数组
注意：
1.因为结果数组需要用到数组的坐标，因为需要在声明的时候就标清楚。
但是本题中结果数组的大小是通过map决定的，因此map的大小确定了之后才能去定数组大小，所以DFS方法要写在数组声明之前。
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
private:
    map<int,map<int,vector<int>>>mapmap;
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        helper(root,0,0);
        vector<vector<int>>ans(mapmap.size());
        int index = 0;
        for(auto m :mapmap){
            for(auto t : m.second){
                sort(t.second.begin(),t.second.end());
                for(auto p : t.second){
                    ans[index].push_back(p);
                }
            }
            ++index;
        }
        return ans;
    }
    
    void helper(TreeNode* root, int weight, int height){
        if(!root)return;
        mapmap[weight][height].push_back(root->val);
        helper(root->left,weight-1,height+1);
        helper(root->right,weight+1,height+1);
    }
};