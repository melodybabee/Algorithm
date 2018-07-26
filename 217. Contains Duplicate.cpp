class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        if(nums.size() == 1) return false;
        if(nums.empty()) return false;
        
        for (int i = 0; i < nums.size() -1; ++i){
            for (int j = i+1; j < nums.size(); ++j)
                if(nums[i] == nums[j])
                    return true;
        }
        return false;
        
    }
};
/*
设计思路：
1.循环vector,如果一旦有相等，return true,否则return false
2.如果为0，return false
3.如果只有一个元素，return false

注意：
1.区分“=”和“==”
2.判断vector是否为空，要用nums.empty()

优化：
1.本题时间复杂度很高，注意后面的优化
*/