题意：
输出数组中连续的子数组。
思路：
1.类似163找缺失的子数组，用一个左指针指向左边界，右指针开始循环。如果数组是依次递增的，那么右指针不断向右移动。
2.一旦不是依次递增，那么判断左右指针的距离，如果是1，输出左指针指向的位置。
如果大于1，那么返回左右指针之间的距离。
3.左指针移动到右指针的当前位置继续循环。
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ans;
        int i = 0;
        while(i < nums.size()){
            int j = 1;
            while(i + j < nums.size() && nums[i+j] - nums[i] == j) ++j;
            if(j == 1) ans.push_back(to_string(nums[i]));
            else ans.push_back(to_string(nums[i]) + "->" + to_string(nums[i+j-1]));
            i += j;
        }
        return ans;
    }
};