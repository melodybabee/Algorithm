题意：
给一个三角形，找到从头到尾的最小和。
思路：
1.题意中说明了每一行只能找它所在位置下一行的邻接位置，因此是在求约束条件下的最短路径，利用DP的思路。
2.从题意出发，可以想到建立一个和三角形一样大的矩阵，更新结点的值。从(i,j)开始到底部的最小路径和是MP(i,j)，状态转移方程是MP(i,j)=min{MP(i+1,j),MP(i+1,j+1)}+triangle[i][j]；
以此类推：
MP(0,0)=min{MP(1,0),MP(1,1)}+triangle[0][0];
MP(1,0)=min{MP(2,0),MP(2,1)}+triangle[1][0];
MP(1,1)=min{MP(2,1),MP(2,2)}+triangle[1][1];
会发现有大量重复计算的部分，在计算过程中一直存在计算式。因此这种由上向下的DP可以更改为由下向上的DP。
3.那么只需要一个一维数组，首先更新的是三角形中过的最后一行元素，每次向上更新。
MP(n,0)=triangle[n][0];
MP(n,1)=triangle[n][1];
MP(n,2)=triangle[n][2];
MP(n-1,0)=min{MP(n,0),MP(n,1)}+triangle[n-1][0];
MP(n-1,1)=min{MP(n,1),MP(n,2)}+triangle[n-1][1];
以此类推
MP(1,0)=min{MP(2,0),MP(2,1)}+triangle[1][0];
MP(1,1)=min{MP(2,1),MP(2,2)}+triangle[1][1];
MP(0,0)=min{MP(1,0),MP(1,1)}+triangle[0][0];
4.最后返回这个数组的[0]这个位置就是做求的结果
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int>dp(triangle.back());
        int n = triangle.size();
        for(int i = n-2; i >= 0; --i){
            for(int j = 0; j < triangle[i].size();++j){
                dp[j] = min(dp[j],dp[j+1]) + triangle[i][j];
            }
        }
        return dp[0];
    }
};