题意：
找到数组中和小于目标值的所有数组的个数
思路：
1.类似015 3sum的方法，用双指针确定出来范围，因为是找到小的，所以一旦满足，那么以左指针为起点，到右指针之间的所有数组都可以满足情况。
因此用right-left得到就可以，再去扩大左指针的位置
2.如果大于等于指定的值，那么不断缩小右指针即可。
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int count = 0;
        sort(nums.begin(),nums.end());
        for(int i = 0; i < nums.size(); ++i){
            int temp = target-nums[i];
            int left = i+1;
            int right = nums.size()-1;
            while(left < right){
                if(nums[left] + nums[right] < temp){
                    count += (right-left);
                    ++left;
                }else{
                    --right;
                }
            }
        }
        return count;
    }
};