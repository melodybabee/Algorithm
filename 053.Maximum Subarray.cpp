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