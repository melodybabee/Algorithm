题意：
062的follow up，在矩阵中加入数值为1的障碍，遇到不可通过，问有几种走法。
思路：
1.声明一个二维数组，开始遍历原数组，如果为0，新数组置为1；如果为1，新数组从当前位开始后面都置为0.
这样更新新数组的第一列和第一行，
2.开始遍历新数组，如果在中间遇到原数组中等于1的位置，那么置为0，表示没有线路。
3.最后输出右下角位置的值。
注意：
1.需要注意如果1形成了屏障，那么就无法通过，由此会产生很多corner cases需要注意。
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        int i;
        int j;
        vector<vector<int> > dp(m, vector<int>(n, 1));
        if(obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1) return 0;
        for(i = 0; i < m; ++i){
            if(obstacleGrid[i][0]==0) dp[i][0] = 1;
            else break;
        }
        while(i < m){
            dp[i][0] = 0;
            ++i;
        }
        for (j = 0; j< n ; ++j){
            if(obstacleGrid[0][j]==0) dp[0][j] = 1;
            else break;
        }
        while(j < n){
            dp[0][j] = 0;
            ++j;
        }
        for(i = 1; i < m; ++i){
            for (j = 1; j < n ; ++j){
                if(obstacleGrid[i][j] == 1) dp[i][j] = 0;
                else dp[i][j] = dp[i][j-1] + dp[i-1][j];
            }
        }
        return dp[m-1][n-1];
    }
};
优化：
当遇到为1的点，将该位置的dp数组中的值清零。
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid.empty() || obstacleGrid[0].empty() || obstacleGrid[0][0] == 1) return 0;
        vector<vector<int> > dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), 0));
        for (int i = 0; i < obstacleGrid.size(); ++i) {
            for (int j = 0; j < obstacleGrid[i].size(); ++j) {
                if (obstacleGrid[i][j] == 1) dp[i][j] = 0;
                else if (i == 0 && j == 0) dp[i][j] = 1;
                else if (i == 0 && j > 0) dp[i][j] = dp[i][j - 1];//列
                else if (i > 0 && j == 0) dp[i][j] = dp[i - 1][j];//行
                else dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp.back().back();//最后一个vector中的最后一个元素
    }
};

1.19复习：
注意：
因为原数组中的1表示的是障碍，因此如果原数组中为1，那么在dp数组中的值就为0
左上角以及第一行和第一列需要分别更新，最后再更新dp数组。返回DP数组的最后一位上的值
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        vector<vector<int>>dp(obstacleGrid.size(),vector<int>(obstacleGrid[0].size(),0));
        for(int i = 0; i < dp.size(); ++i){
            for(int j = 0; j < dp[0].size(); ++j){
                if(obstacleGrid[i][j] == 1) dp[i][j] = 0;
                else if(i == 0 && j == 0)dp[i][j] = 1;
                else if(i == 0) dp[i][j] = dp[i][j-1];
                else if(j == 0) dp[i][j] = dp[i-1][j];
                else dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp.back().back();
    }
};
