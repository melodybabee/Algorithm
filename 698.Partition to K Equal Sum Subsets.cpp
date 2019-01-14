题意：416 follow up,判断数组中的数字能否被平均分为K份
思路：
1.首先依然先对数组求和，判断是否满足整除目标值，如果不能整除，直接返回false
2.对数组中的数字进行递归，需要一个visited数组来记录每一个数字是否被遍历过，还需要一个临时变量来记录当前的宗旨，起始位置
3.递归的边界条件是如果只剩下最后一组了，那么直接返回true;
如果当前的总和等于目标值，那么对k-1，同时从头进行下一位的递归
4.进入正常的遍历环节是如果没有遍历过的数字，标记为true,同时累加上当前的和进入下一次递归
递归结束如果为true就依次返回
5.如果不是true,那么注意需要把visited数组更改为false,重新下一位的循环
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(nums.begin(),nums.end(),0);
        if(total % k != 0) return false;
        vector<bool>visited(nums.size(),false);
        return helper(nums, k, total/k, 0, 0,visited);
    }
    
    bool helper(vector<int>& nums, int k, int target,int start, int curtotal,vector<bool>&visited){
        if(k == 1) return true;
        if(curtotal == target) return helper(nums,k-1,target,0,0,visited);
        for(int i = start; i < nums.size(); ++i){
            if(visited[i]) continue;
            visited[i] = true;
            if(helper(nums,k,target,i,curtotal + nums[i],visited)) return true;
            visited[i] = false;
        }
        return false;
    }
};