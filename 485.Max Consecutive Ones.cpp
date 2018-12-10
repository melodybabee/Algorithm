题意：
找到字符串中最多的连续1的个数。
思路：
1.遍历数组，如果等于1，那么取结果值和当前坐标到左边界之间的长度。
2.如果不为1，更新左边界，left记录的是值为1的子串的第一个坐标位置。
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int ret = 0;
        int left = 0;
        for(int i = 0; i < nums.size();++i){
            if(nums[i] == 1){
                ret = max(ret,i-left+1);
            }else{
                left = i+1;
            }
        }
        return ret;
    }
};