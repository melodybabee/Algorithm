题意：
找到两个数组中长度最长的相同子数组。
思路：
1.极值问题首先想DP。dp[i][j]表示数组A的前i个数字和数组B的前j个数字的最长子数组的长度
状态转移方程：dp[i][j] = dp[i-1][j-1]+1
2.对于两个数组而言，只有前一位匹配上，后一位才能匹配。因此如果两个数组的某一位相等，dp[i][j]值等于1+dp[i-1][j-1]的值。
如果某两位不相等，那么直接置为0。
3.最后返回dp中的最大值
注意：
1.首先需要把dp数组置为0，那么第0行和第0列都是0，真正有效的部分从第1行和第一列开始
因此dp初始化的时候需要比两个数组的size()还要大1，并从1开始循环。
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        vector<vector<int>>dp(A.size()+1,vector<int>(B.size()+1,0));
        int ans = 0;
        for(int i = 1; i< dp.size(); ++i){
            for(int j = 1; j < dp[i].size(); ++j){
                dp[i][j] = (A[i-1]==B[j-1])? dp[i-1][j-1]+1 : 0;
                ans = max(ans,dp[i][j]);
            }
        }
        return ans;
    }
};