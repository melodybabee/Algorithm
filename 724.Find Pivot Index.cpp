题意：找到数组中的位置，满足该位置左侧所有值的和等于该位置的右侧所有值的和。
思路：
1.首先计算出数组的总和，再依次遍历数组。用一个临时变量不断相加，如果这个变量的值等于sum,那么返回坐标的位置。
2.否则用sum减去当前位置上的值。
3.如果遍历结束都还没有返回某个坐标，那么返回-1。
注意：
1.不能用双指针一左一右进行遍历相加的原因是，这种方法需要判断移动哪一边的指针。
如果按照谁小移动谁的规则的话，那么遇到负数无法处理。因此方法不适用。
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        int l = 0;
        for(int i = 0; i < nums.size(); ++i){
            l += nums[i];
            if(l == sum) return i;
            sum -= nums[i];
        }
        return -1;
    }
};