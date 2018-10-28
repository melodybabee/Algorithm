题意：
找到方形中从第一行到最后一行的最小和，在下一行只能找上一行的相邻元素。类似120Triangle。
思路：
1.用一个一维数组记录下最后一行的值，更新数组，上一行的第一个值等于自己+下一行范围内两个值的较小值
上一行的最后一个值等于自己+下一行范围内两个值的较小值
其他位置等于自己+下一行范围内三个值的较小值
2.【注意】因为更新过后的的值有可能会被下一位继续计算，因此还需要建立一个数组来作为暂存数组，结束内循环后交换
3.最后输出dp数组中的最小值
注意：
1.请你区分if...if...和if...else if...不要再因为这样低级错误debug了
2.在最后输出的时候先把ret置为首位，再去小
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) {
        int m = A.size();
        int n = A[0].size();
        int ret = 0;
        vector<int>dp;
        for(int i = 0; i < n; ++i){
            dp.push_back(A[m-1][i]);
        }
        for(int i = m-2; i>=0; --i){
            vector<int>dp2(dp.size(),0);
            for(int j = 0; j< n ;++j){
                if(j == 0) dp2[j] = min(A[i][j]+dp[j],A[i][j]+dp[j+1]);
                else if(j == n-1) dp2[j] = min(A[i][j]+dp[j],A[i][j]+dp[j-1]);
                else dp2[j] = A[i][j]+min(min(dp[j],dp[j+1]),dp[j-1]);
            }
            dp = dp2;
        }
        ret = dp[0];
        for(int i = 0;i<dp.size();++i){
            ret = min(ret,dp[i]);
        }
        return ret;
    }
};
优化：
1，因为是n*n的数组对齐的，所以不用新建数组。从最后一排开始依次向上更新即可。
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) {
        int sum =0;
        for (int i = A.size()-2; i>=0; --i){
            for (int j = 0; j < A[0].size(); ++j){
                if (j>0 && j <A[0].size()-1)
                    A[i][j] += min(A[i+1][j], min(A[i+1][j-1], A[i+1][j+1]));
                else if (j == 0)
                    A[i][j] += min(A[i+1][j], A[i+1][j+1]);
                else 
                    A[i][j] += min(A[i+1][j],A[i+1][j-1]);
            }
        }
        sum = A[0][0];
        for (int i=0; i <A[0].size(); ++i)
        if (sum > A[0][i])
            sum = A[0][i];
        return sum;
    }
};