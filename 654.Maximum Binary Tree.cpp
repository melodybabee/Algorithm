题意：
找出最大的二叉树。
思路：
1.首先需要理清题意，数组中最大的数字作为根，根左是左子树，根右是右子树。明显用递归解决问题。
注意不能改变数组中的顺序，因此不能在最开始用sort排序，需要遍历找到数组中的最大值。
2.找到最大值后作为根，左右分别形成一个新的数组，对根左和根右进行递归。
3.最后返回根。
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if(nums.empty()) return NULL;
        int max = nums[0];
        int index = 0;
        for(int i= 0 ; i < nums.size(); ++i){
            if(nums[i] > max){
                max= nums[i];
                index = i;
            }
        }
        TreeNode* root = new TreeNode(max);
        vector<int> left = vector<int>(nums.begin(),nums.begin()+index);
        vector<int> right = vector<int>(nums.begin()+index+1,nums.end());
        root -> left = constructMaximumBinaryTree(left);
        root -> right = constructMaximumBinaryTree(right);
        return root;
    }
};

优化：
不需要每次新建数组。仍然递归。
注意：
1.因为数值最大的点已经作为根结点，所以递归的时候左子树的右边界是mid-1,右子树的左边界是mid+1
2.找最大值的时候要遍历到结尾的值
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if(nums.empty()) return NULL;
        return helper(nums,0,nums.size()-1);
    }
    
    TreeNode* helper(vector<int>& nums, int start, int end){
        if(start > end) return NULL;
        int mid = start;
        for(int i = start; i <= end; ++i){
            if(nums[i] > nums[mid])
                mid = i;
        }
        TreeNode* root = new TreeNode(nums[mid]);
        root -> left = helper(nums,start,mid-1);
        root -> right = helper(nums,mid+1,end);
        
        return root;
    }
};

方法二：用一个数组来维护降序
思路：
1.如果比尾部元素小，方法右侧；如果比尾部元素大，把尾部元素加在左侧，同时pop_back()尾部元素。直到数组为空或者尾部元素较大为止。
2.最后把循环到的结点push到数组中，
3.返回数组中的第一个位置。
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode*>vec;
        for(auto num :nums){
            TreeNode* node = new TreeNode(num);
            while(!vec.empty() && vec.back()->val < node -> val){
                node -> left = vec.back();
                vec.pop_back();
            }
            if(!vec.empty()){
                vec.back() -> right = node;
            }
            vec.push_back(node);
        }
        return vec.front();
    }
};