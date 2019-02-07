class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0;
        int ret = nums[0];
        for (int i = 0; i< nums.size();++i){
            sum += nums[i];
            if(sum > ret){
                ret = sum;
            }
            if(sum < 0){
                sum = 0;
            }
        }
        return ret;
    }
};

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> ret(nums.size(),0);
        ret[0] = nums[0];
        int ans = nums[0];
        for (int i = 1; i< nums.size();++i){
            ret[i] = max(nums[i],ret[i-1]+nums[i]);
            ans = max(ret[i],ans);
        }
        return ans;
    }
};
/*
设计思路：
【法1】：循环解法
1.循环整个vector,先将结果保存ret，后面依次相加sum，比较，保留较大的那个为ret
2.如果sum结果小于0，置为0
3.循环结束之后返回ret

注意：
1.本题的思路重点在于一个数与负数相加只会越加越小，大数才会越加越大。因此如果相加结果为负，直接置为0即可。指针指向顺序是依次相加以头元素开始的子串，某段子串小于0后，舍弃

【法2】：动态规划+divide and conquer
1.首先将本题的问题分析，发现可以分成小问题。从全局来看，所有的子串都可以用该元素+其所有元素构成的子串进行表示
2.因此如果想要找到最大和，首先可以找到以每位字符为结尾的子串的最大值，再从中找到最大的
3.s表示某一位，ret表示总和
  （最优子结构<单句>，边界值<此题为0>，状态转移方程<从1到n>）
  ret[1]max = s1 + ret[0]max;
  ret[2]max = s2 + ret[1]max;
  ret[3]max = s3 + ret[2]max;
  ret[n]max = sn + ret[n-1]max;
  再比较ret中最大的值。
4.用ans记录下ret的值的比较结果，从中比较出max值,返回ans

注意：
1.因为ret需要通过每位进行比较，并存储下来，因此需要创建一个新的vector
2.如果vector用到下标，在声明的时候就要声明出元素，如果vector为空是不能用到下角标的，可以先都声明为0

*/

三刷：
注意：
1.本题的关键之处就在于如果过程中的和小于0，那么把求和的结果更改为0，重新计算，因为如果是负数那么会越加越小。
2.负数直接舍弃就可以，因为如果能够在负数的基础上变大，一定是正数相加，而再相加也不如直接返回一个正数的值大。
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ret = nums[0];
        int sum = 0;
        for(int i = 0; i< nums.size(); ++i){
            sum += nums[i];
            ret = max(ret,sum);
            if(sum < 0) sum = 0;
        }
        return ret;
    }
};

DP:
1.dp[i]表示[0,i]位置上能够获得的最大值，动态转移方程是当前的值，与当前的值+之前的最大值，两者之间的较大值。
2.注意因为在更新dp的过程中会使结果减小，因此需要一个结果值来记录过程中产生的最大值，最后返回。
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int>dp(nums.size());
        dp[0] = nums[0];
        int ret = nums[0];
        for(int i = 1; i < nums.size();++i){
            dp[i] = max(dp[i-1]+nums[i],nums[i]);
            ret = max(dp[i],ret);
        }
        return ret;
    }
};

2.6复习
DP[i]表示从0-i范围内的最大值，因为动态转移方程就是dp[i] = (dp[i-1]+nums[i],nums[i]),如果当前位数最大那么可以舍弃掉之前的所有子串
用一个结果值记录在过程中出现的最大值，因为有可能较大值出现在中间
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int>dp = nums;
        int ret = nums[0];
        for(int i = 1 ; i < dp.size(); ++i){
            dp[i] = max(nums[i],dp[i-1]+nums[i]);
            ret = max(ret,dp[i]);
        }
        return ret;
    }
};
遍历的方法注意舍弃掉负数的情况，因为每个坐标的位置都可以单独存在，那么如果是负数会使整体的结果肯定比单独一个元素要小，直接舍弃为0即可。
