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
方法三：位运算方法待学习
