题意：
给一个矩阵，找到从左上到右下的所有路径，输出一共有多少种情况。
思路：
1.利用动态规划建立一个二维矩阵，初始值为1，每一位更新的新坐标值等于它的左加它的上
2.最后返回矩阵的右下角坐标即可
注意：
1.矩阵初始值为0，大小与给定大小的矩阵相同
2.从（1，1）开始更新，因为矩阵从0开始，所以返回的坐标是(m-1)(n-1)
3.在返回的过程中因为需要用到i,j，因此i,j需要设置为全局变量，同时循环还是从1开始
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> vec(m,vector<int>(n,1));
        int i = 1, j = 1;
        for(i = 1; i < m; ++i){
            for(j = 1; j < n; ++j){
                vec[i][j] = vec[i-1][j] + vec[i][j-1];
            }
        }
        return vec[m-1][n-1];
    }
};
优化：也可以用一个一维数组来做动态规划，因为想求的结果是左+上，上一个一维数组记录了上一行的所有值，更新的时候在上一行数组的基础之上加上左侧的元素值即可。
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; ++i) {//行
            for (int j = 1; j < n; ++j) {//列
                dp[j] += dp[j - 1]; 
            }
        }
        return dp[n - 1];
    }
};
优化2：数学方法
这个问题背后的数学模型，其实就是机器人总共走m+n-2步，其中m-1步往下走，n-1步往右走，本质上就是一个组合问题。
也就是从m+n-2个不同元素中每次取出m-1个元素的组合数。
【组合数公式待学习】
public int uniquePaths(int m, int n) {
    double dom = 1;
    double dedom = 1;
    int small = m<n? m-1:n-1;
    int big = m<n? n-1:m-1;
    for(int i=1;i<=small;i++)
    {
        dedom *= i;
        dom *= small+big+1-i;
    }
    return (int)(dom/dedom);
}