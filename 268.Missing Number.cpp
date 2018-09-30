高斯公式：
T（O） = O（n),S(O) = 1
思路：
1.利用等差数列的性质，缺失的数字肯定是完整的数列和减去现在的和，因此首先求出现在的和，用原有的总和减去现在的和即为缺失值
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int ret= 0;
        for(int i = 0; i< nums.size();++i){
            ret += nums[i];
        }
        return nums.size()*(nums.size()+1)/2 -ret;
    }
};

位运算：
T（O） = O（n),S(O) = 1
思路：
1.因为观察到vector中的数字和数组下标有关系，是0-nums.size()中间确实的一位
2.因为位计算中相同为0，不同为1，因此如果遍历数组，把所有值和数组下标过一遍之后，依次做异或运算，会剩出nums.size()和缺失的值的下标
3.因此直接初始化一个数组长度参与计算，这样剩下的元素就是缺失的值
注意；
1.异或：^运算，相同为0，不同为1
2.与：&都是1为1，否则为0
3.或：| 有1为1，都是0的时候为0
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int ret = nums.size();;
        for(int i = 0; i< nums.size();++i){
            ret ^= i ^ nums[i];
        }
        return ret;
    }
};

二叉搜索：
思路：
1.从数组位置的中值开始查找，如果小于数组值，说明下标左侧值缺失，再通过二叉搜索进行查找
2.如果大于等于下标，则缺失值在右侧，不断用left靠近中指即可，最后返回left或者right都可以
注意：
1.right和left包括最后的返回值都是指数组下标，因此可以准确返回缺失的元素
2.本题的所有元素是从0开始的，因此可以与数组下标完全对应
3.如果缺失值在中值右侧，注意是大于等于下标
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int left = 0;
        int right = nums.size();
        while(left < right){
            int mid = left + (right - left)/2;
            if(mid < nums[mid])  right = mid;
            else{
                left = mid+1;
            }
        }
        return right;
    }
};