class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        
        for(int i = 0; i < nums.size(); ++i){
            if(target <= nums[i]){
                return i;
            }
            if(target > nums[i]){
                continue;
            }
              
        }
        return nums.size();
        
    }
};
/*
设计思路：
1.循环vector,如果target小于等于循环到的值，直接return这一位
2.如果target大于循环值，继续循环
3.如果循环体结束还没有return的值，说明target应该放在最后一位，直接return vector的长度
*/