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

12.10复习：
注意：
1.每一位都要判断是否相等。
2.注意nums为空等等需要返回{}的情况。
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if(nums.empty()) return {};
        if(nums.size() <= 2) return {};
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        for(int i = 0 ; i < nums.size()-3;++i){
            if(i > 0 && nums[i] == nums[i-1]) continue;
            for(int j = i+1; j < nums.size();++j){
                if(j> i+1 && nums[j] == nums[j-1]) continue;
                int temp = target - nums[i] - nums[j];
                int left = j+1;
                int right = nums.size()-1;
                while(left < right){
                    if(nums[left] + nums[right] == temp){
                        ans.push_back({nums[i],nums[j],nums[left],nums[right]});
                        while(left < right && nums[left] == nums[left+1]) ++left;
                        while(left < right && nums[right] == nums[right-1]) --right;
                        ++left;
                        --right;
                    }else if(nums[left] + nums[right] < temp){
                        ++left;
                    }else --right;
                }
            }
        }
        return ans;
    }
};