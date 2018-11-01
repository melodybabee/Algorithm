题意：
数组中有重复的数字，输出一个数组中所有不重复的子数组。078 follow up去重。
方法一：递归
思路：
1.依次从第一位开始push数组中的数字，在第一次遍历的时候不用判断是否重复。回溯的时候需要判断下一位是否与上一位重复。
2.去重方法与015 3sum类似，只要下一位与这一位相等且不超过数组范围，那么一直向右移动。
3.注意因为给定的数组不是有序的，因此需要先排序
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        if(nums.empty()) return {};
        vector<int> temp;
        vector<vector<int>> ret;
        sort(nums.begin(),nums.end());
        FindSubsets(nums,0,temp,ret);
        return ret;
    }
    void FindSubsets(vector<int>& nums,int start, vector<int>&temp,vector<vector<int>>&ret){
        ret.push_back(temp);
        for(int i = start; i < nums.size(); ++i){
            temp.push_back(nums[i]);
            FindSubsets(nums,i+1,temp,ret);
            temp.pop_back();
            while(i+1 < nums.size() && nums[i+1] == nums[i]) ++i;
        }
    }
};
方法二：遍历
思路：
1.同样使用078的遍历方法，只不过每当遍历到一个数字与之前的数字相同的话，那么只需要在上一次遍历生成的数字后面push_back即可
2.那么需要一个last来记录上次处理到的数字，如果不等，更新last的位置，如果相等，跳过相等的部分，只更新上一次生成的部分。
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ret{{}};
        sort(nums.begin(),nums.end());
        int size = 1;
        int last = nums[0];
        for(int i = 0; i< nums.size();++i){
            if(nums[i] != last){
                last = nums[i];
                size = ret.size();
            }
            int newsize = ret.size();
            for(int j = newsize-size; j < newsize; ++j){
                ret.push_back(ret[j]);
                ret.back().push_back(nums[i]);
            }
        }
        return ret;
    }
};