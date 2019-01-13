题意：
找到数组中能整除目标值的区间个数。
方法一：DP+暴力解
TLE
思路：一个从头部开始循环，一个接着前一个指针进行更新和，判断是否可以整除。数据量大的时候会TLE
class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        int total = 0;
        for(int i = 0; i < A.size();++i){
            vector<int>dp(A.size(),0);
            dp[i] = A[i];
            for(int j = i; j < A.size(); ++j){
                dp[j] = dp[j-1] + A[j];
                if(dp[j] % K == 0) ++total;
            }
        }
        return total;
    }
};
方法2:Prefix Sums前缀和【重点复习】
思路：
1.前缀和的意思是该项上的值等于所有它之前的值的和，本题中表示之前所有位数上的数字的和被整除后的余数
2.首先遍历所有数字，建立一个map来记录某个前缀和上对应的个数是多少
如果在map中没有出现过这个前缀和，表示不能对新的数字进行整除，那么在map中形成这个映射
如果出现过这个key值，表示新的数字可以进行整除，那么结果值需要加上当前前缀和的value值，表示当前数字以及当前数字与之前连接的位置可以被整除
实际上前缀和是以每一位数字的为结尾的数组为基准的
3.为了让prefix的结果在[0，K）范围内，需要用(prefix+a%K+K)%K来保证余数为正
4.最后返回结果值
class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        unordered_map<int,int>map;
        map[0] = 1;
        int prefix = 0;
        int ret = 0;
        for(auto a :A){
            prefix  = (prefix + a%K + K)%K;
            ret += map[prefix];
            ++map[prefix];
        }
        return ret;
    }
};
