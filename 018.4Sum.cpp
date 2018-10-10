题意：
找出数组中和等于目标值的子数组，子数组包含4个元素
思路：
1.所有N sum的题目都是固定前N-2个元素，用两个指针来遍历后面的数组，再依次向中间靠近
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ret = {};
        if(nums.empty()) return ret;
        if(nums.size() <= 2) return ret;
        sort(nums.begin(),nums.end());
        for(int i = 0; i<nums.size()-3; ++i){
            if(i > 0 && nums[i] == nums[i-1]) continue;
            for(int j= i+1; j < nums.size() - 2; ++j){
                if(j > i+1 && nums[j] == nums[j-1]) continue;
                int p = j+1;
                int q = nums.size()-1;
                while(p < q){
                    if(nums[i] + nums[j] + nums[p] + nums[q] == target){
                        ret.push_back({nums[i],nums[j],nums[p],nums[q]});
                        while(p < q && nums[p+1] == nums[p]) ++p;
                        while(p < q && nums[q-1] == nums[q]) --q;
                        ++p;
                        --q;
                    }else if (nums[i] + nums[j] + nums[p] + nums[q] < target){
                        ++p;
                    }else{
                        --q;
                    }
                }
            }
        }
        return ret;
    }
};