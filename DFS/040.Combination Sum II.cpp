题意：
039的变形，给定的数组中的数字不可以重复使用，在输出的数组中也不能出现相同的结果。
思路：
1.大体上的回溯+递归与039完全相同，只不过在for循环中递归的时候需要走到当前位置的下一位
2.同时进入下一位以后需要判断有无重复值
此处注意区分在一个结果中的重复值，比如[1,2,2]和[1,2,2][1,2,2]是不同的。
可以在结果中有重复的值，表示我在重新进入递归的时候可以有相同的值。
但是在同一个递归函数中，如果我把最后一位去掉了之后，头指针指向的位置会向后移动，这时就不能再有重复的值。
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int>temp;
        vector<vector<int>> ret;
        sort(candidates.begin(),candidates.end());
        dfs(candidates,target,0,temp,ret);
        return ret;
    }
    
    void dfs(vector<int>& candidates,int target,int start,vector<int>&temp,vector<vector<int>>&ret){
        if(target < 0) return;
        if(target == 0) return ret.push_back(temp);
        else{
            for(int i = start; i < candidates.size();++i){
                if(i>start && candidates[i] == candidates[i-1]) continue;
                temp.push_back(candidates[i]);
                dfs(candidates,target-candidates[i],i+1,temp,ret);
                temp.pop_back();
            }
        }
    }
};

2.6.复习
注意：039follow up,只不过一个数字不可以重复进行计算，因此进入DFS递归需要到下一位上
同时如果相邻的两个数字挨着的是相同的，那么在循环遍历的时候需要跳过，因为DFS可以把他们计算进去，但是如果循环过程中有重复的数字，那么在最后的结果中会有重复的子结果。
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<vector<int>>ans;
        vector<int>ret;
        dfs(candidates,ans,ret,target,0);
        return ans;
    }
    
    void dfs(vector<int>& candidates, vector<vector<int>>&ans,vector<int>&ret,int target,int start){
        if(target < 0) return;
        else if (target == 0) ans.push_back(ret);
        else{
            for(int i = start; i < candidates.size(); ++i){
                if(i > start && candidates[i] == candidates[i-1]) continue;
                ret.push_back(candidates[i]);
                dfs(candidates,ans,ret,target-candidates[i],i+1);
                ret.pop_back();
            }
        }
    }
};