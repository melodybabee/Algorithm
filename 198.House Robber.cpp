class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        vector<int> ret(nums.size(),0);
        if(nums.size() > 0) ret[0] = nums[0];
        if(nums.size() > 1) ret[1] = max(nums[0],nums[1]);
        for(int i = 2; i < nums.size();++i){
            ret[i] = max(nums[i]+ret[i-2], ret[i-1]);
        }
        return ret[ret.size()-1];
    }
};

思路：
1.本题的题意实际在求一个数组中，取出一个或多个不相邻的数字，使其和最大
2.那么每到一个新的位置n，只有两种选择，要不是用其前[n-2]项的和加上该位数字，要不是取其前[n-1]的和
那么可以得到状态转移方程是：ret[i] = max(nums[i]+ret[i-2], ret[i-1])；
3.观察方程，可以新建一个array,同时在外部确定好i = 0, i = 1, i = 2 的值，从i=2的时候开始循环
4.最后返回ret数组的最后一位

优化：
1.在i= 1, i = 0的时候可以直接优化为相应的结果，不需要用不等式判断
2.不需要新建数组操作，因为原数组储存新值是在进行比较过后，因此在原数组中操作接即可
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) nums[0];
        nums[1] = max(nums[0],nums[1]);
        for(int i = 2; i < nums.size();++i){
            nums[i] = max(nums[i]+nums[i-2], nums[i-1]);
        }
        return nums[nums.size()-1];
    }
};

注意：
1.所有的DP递推都可以写成递归的方式，区别在于递归每次都需要从上至下计算，会重复计算很多子元素，因此用DP效率更高