题意：有重复数字的全排列，在结果中不能出现重复的排列结果
思路：
1.是全排列(046)这道题的fellow up,与40题在于39题基础上的fellow up相同。
2.因为给出的数字会有重复的情况，有重复的数字在输出中算一种答案，因此需要加上一步判断重复
3.当这一点没有被循环过时，如果它与前一位相等，且不是第一次循环，且它的前一位也没有被标记过的以后，跳过
注意区分递归过程中的重复元素，和进行for循环中的重复元素。前者是i不动的前提下将后面所有的数字依次push_back,后者是确定从哪一位开始循环，在循环的过程中会有新的递归输出所有数字
注意：
在设置标志位大小的时候，因为含义是几个false,因此需要设置的大小事nums.size();
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> temp;
        vector<vector<int>> ret;
        vector<bool> flag(nums.size(),false);
        sort(nums.begin(),nums.end());
        dfs(nums,0,temp,ret,flag);
        return ret;
    }
    void dfs(vector<int>& nums,int start,vector<int>&temp,vector<vector<int>>&ret,vector<bool> flag){
        if(start == nums.size()) ret.push_back(temp);
        else{
            for(int i = 0; i < nums.size(); ++i){
                if(flag[i] == false){
                    if(i > 0 && nums[i] == nums[i-1] && flag[i-1] == false) continue;
                    flag[i] = true;
                    temp.push_back(nums[i]);
                    dfs(nums,start+1,temp,ret,flag);
                    temp.pop_back();
                    flag[i] = false;
                }
            }
        }
    }
};