题意：
找到最长的上下波折的子数组。
思路：
1.通过观察发现，如果遍历一次数组，处于山峰或者山谷的值记录为3，如果不满足条件记录为0，那么最后的结果就是最长的连续个3长度
2.把上面的结果更新为dp数组。
3.遍历DP数组，计算最多的连续个3的个数，最后如果结果为0，返回2，如果不为0，返回连续个3的个数+2
class Solution {
public:
    int maxTurbulenceSize(vector<int>& A) {
        if(A.size() == 1) return 1;
        vector<int>dp(A.size(),0);
        dp[0] = dp[A.size()-1] = 2;
        for(int i = 1; i < A.size()-1; ++i){
            if(A[i] > A[i-1] && A[i] > A[i+1]) dp[i] = 3;
            else if(A[i] < A[i-1] && A[i] < A[i+1]) dp[i] = 3;
        }
        int ans = 0;
        int count = 0;
        for(int i = 1; i < dp.size(); ++i){
            if(dp[i] != 3){
                count = 0;
            }
            if(dp[i] == 3) ++count;
            ans = max(ans,count);
        }
        return ans == 0 ? 2 : ans +2;
    }
};
优化：滑动窗口，用正负状态来记录在山峰还是山底
思路：
1.用0，-1，1来表示不同的状态，如果当前下一位更小，说明当前在山顶，判断是否结果大于0，如果大于0+1
如果下一位更大，判断是否结果小于0，如果小于0，-1，因为当前值为负数，-1反而更大
2.结果值取过程中的较大值
3.每次进入遍历都需要对原结果取反
4.最后返回结果值+1
class Solution {
public:
    int maxTurbulenceSize(vector<int>& A, int ret = 0) {
        for(int i = 0,count = 0; i < A.size()-1; ++i, count *= -1){
            if(A[i] > A[i+1]) count = count >= 0 ? count +1 : 1;
            else if(A[i] < A[i+1]) count = count <= 0 ? count - 1 : -1;
            else count = 0;
            ret = max(ret,abs(count));
        }
        return ret+1;
    }
};
