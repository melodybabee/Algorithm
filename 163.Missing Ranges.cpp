题意：
找到在跟定范围内缺失的数组范围。
思路：
1.设立两个指针分别指向数组的左边界，和用来循环数组。
2.当左等于右的时候，说明没有间隙，左指针向右移动。如果左小于右，说明有间隙，如果间隙为1，那么返回左，大于1，返回右-1-左这个范围
注意：
1.把int转换位string的方法是to_string()即可
2.题目中给出的范围是会大于等于原数组的，请仔细读题。因此可以把lower作为左边界，把upper作为右边界。
3.如果数组右边界小于upper,还需要输出upper到数组右边界的值，那么首先需要进入循环，即i <= nums.size(),进入循环后再次判断如果超出范围或大于upper,那么right移动到upper后面。
4.注意因为使用了upper+1,那么如果upper是INT_MAX的话就会超过int范围，所以left和right需要声明为long long,upper也需要重新定义为long long 

class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> ret;
        long long left = lower;
        long long right;
        long long up = upper;
        if(nums.empty()) {
            if(upper == lower) ret.push_back(to_string(lower));
            else ret.push_back(to_string(lower) + "->" + to_string(upper));
            return ret;
        }
        for(int i = 0; i <= nums.size(); ++i){
            if(i < nums.size() && nums[i] <= up){
                right = nums[i];
            }else{
                right = up+1;
            }
            if(left == right) ++left;
            else if (right > left){
                if(right - left == 1) {
                    ret.push_back(to_string(left));
                    left = right +1;
                }else{
                    ret.push_back(to_string(left) + "->" + to_string(right-1));
                    left = right +1;
                }
            }
        }
        return ret;
    }
};