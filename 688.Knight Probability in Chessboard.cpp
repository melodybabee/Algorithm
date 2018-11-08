knight 骑士
题意：
在只能走日子格的棋盘中，判断指定走N次后仍然在棋盘中的概率。
思路：
1.从规定的位置开始行走，每次走日字格，如果走出去了不算，没有走出去记下来该位置。
2.因为一个位置可以有8的选择，因此每一个满足题意的选择的概率是0.125。
3.动态规划用一个2维的数组记录本次行走的位置，不出边界就用上一层位置的概率*0.125
4.再用一个k来记录层数，因此是一个3维数组。最后输出最后一层上所有位置概率的和。
class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        double ret = 0.0;
        double pro = 0.125;
        vector<vector<vector<double>>> dp(K + 1,vector<vector<double>>(N,vector<double>(N,0)));
        dp[0][r][c] = 1;
        for(int k = 1; k <= K; ++k){
            for(int i = 0; i < N; ++i){
                for(int j = 0; j< N; ++j){
                    if(i-1 >= 0 && j-2 >= 0) 
                        dp[k][i][j] += (dp[k-1][i-1][j-2] * pro);
                    if(i-2 >= 0 && j-1 >= 0) 
                        dp[k][i][j] += (dp[k-1][i-2][j-1] * pro);
                    if(i-2 >= 0 && j+1 < N) 
                        dp[k][i][j] += (dp[k-1][i-2][j+1] * pro);
                    if(i-1 >= 0 && j+2 < N) 
                        dp[k][i][j] += (dp[k-1][i-1][j+2] * pro);
                    if(i+1 < N && j+2 < N) 
                        dp[k][i][j] += (dp[k-1][i+1][j+2] * pro);
                    if(i+2 < N && j+1 < N) 
                        dp[k][i][j] += (dp[k-1][i+2][j+1] * pro);
                    if(i+2 < N && j-1 >= 0) 
                        dp[k][i][j] += (dp[k-1][i+2][j-1] * pro);
                    if(i+1 < N && j-2 >= 0) 
                        dp[k][i][j] += (dp[k-1][i+1][j-2] * pro);
                }
            }
        }
        for(int i = 0; i < N; ++i){
            for(int j = 0; j< N; ++j){
                ret += dp[K][i][j];
            }
        }
        return ret;
    }
};