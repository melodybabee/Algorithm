题意：
303follow up,在二维不可变的数组中找到二维指定范围内的和。
思路：
1.本题暴力拆解进行循环会TLE。
2.因此仍然需要利用dp的方法，新建一个二维的DP数组，dp[i][j]表示从(0,0)到(i,j)这个区间内的和。
3.因为dp声明的时候比原数组的长和宽大1，因此两层for循环需要从1开始。
更新的时候即[行-1][列]+[行][列-1]-两次计算中重复的部分+被减去的左上角元素
4.输出的时候是dp(指定位置)-[值大的行][值小的列的前一位]-[值小的行的前一位][值大的列]+被重复减掉的左上角元素
class NumMatrix {
private:
    vector<vector<int>> dp;
public:
    NumMatrix(vector<vector<int>> matrix) {
        if(matrix.empty() || matrix[0].empty()) return;
        dp.resize(matrix.size()+1, vector<int>(matrix[0].size()+1,0));
        for(int i = 1; i <= matrix.size();++i){
            for(int j = 1;  j <= matrix[0].size(); ++j){
                dp[i][j] = dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+matrix[i-1][j-1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row2+1][col2+1]-dp[row2+1][col1]-dp[row1][col2+1]+dp[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */