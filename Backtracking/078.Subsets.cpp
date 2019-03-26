题意：
输出一个数组中的所有子数组。
方法一：遍历循环
思路：
1.首先在vector中输入一个空的{},每次进入第一层循环，判断返回的vector中的长度，进入第二层循环
2.在第二层循环里，把vector中现存的数组都重新输出一次，并在新输出的数组的后面输入i指向的值
3.以[1,2,3]为例，最开始是空集，接着处理1，就在空集上加1，为[1]
现在有两个[]和[1]，下面处理2，在之前的子集基础上，每个都加个2，可以分别得到[2]，[1, 2]
现在所有的子集合为[], [1], [2], [1, 2]，处理3的情况可得[3], [1, 3], [2, 3], [1, 2, 3], 再加上之前的子集就是所有的子集合
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret{{}};
        for(int i = 0; i < nums.size();++i){
            int size = ret.size();
            for(int j = 0 ;j < size;++j){
                ret.push_back(ret[j]);
                ret.back().push_back(nums[i]);
            }
        }
        return ret;
    }
};
方法二：递归回溯
思路：
1.从上到下解决问题，在原数组中，每个数字只有存在或者不存在两种情况，那么在构造子集的时候就选择构造和不构造两种，因此形成回溯
2.每当push进去一个新的数字，进入递归，DFS思想，然后再一次pop_back()出来
注意：
在递归中进入下一层递归的时候是从i+1开始而不是start+1
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> temp;
        vector<vector<int>> ans;
        getSubsets(nums, 0, temp,ans);
        return ans;
    }
    void getSubsets(vector<int>& nums,int start,vector<int>&temp, vector<vector<int>>&ans){
        ans.push_back(temp);
        for(int i = start; i < nums.size();++i){
            temp.push_back(nums[i]);
            getSubsets(nums, i+1, temp,ans);
            temp.pop_back();
        }
    }
};

3.25复习：
回溯法【重点复习】
注意：
1.在helper函数中如何判断是否到了边界,就是每次首先push进去temp数组，因此也会push进去空数组
2.要设置一个起点位置，每次遍历都是从起点位置开始，但是递归的部分是从当前遍历到的位置+1进行下一步递归的
3.回溯思想的核心是要有pop_back()的过程，一旦结束了上一次递归，那么回回到调用递归的函数位置，继续下一步，即弹出的操作
同时再次进入遍历中，如果没到结尾push进去下一位数字
所以[1,2,3]的输出顺序是[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        vector<int> temp;
        helper(ret,temp,nums,0);
        return ret;
    }
    
    void helper(vector<vector<int>> &ret, vector<int> &temp, vector<int>& nums, int start){
        ret.push_back(temp);
        for(int i = start; i < nums.size(); ++i){
            temp.push_back(nums[i]);
            helper(ret,temp,nums,i+1);
            temp.pop_back();
        }
    }
};

两层递归方法：
不断更新数组
注意：
要点在于先把之前的数组复制，再更新进去新的值。
复制的过程就是内层循环完成的，记录当前的数组大小，在结果数组的尾部从头部开始push_back进去原数组。
再在每次新更新的子数组中加入新的元素。
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret {{}};
        for(int i = 0; i < nums.size(); ++i){
            int size = ret.size();
            for(int j= 0; j < size; ++j){
                ret.push_back(ret[j]);
                ret.back().push_back(nums[i]);
            }
        }
        return ret;
    }
};
