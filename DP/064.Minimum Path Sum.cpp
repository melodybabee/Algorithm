题意：
给一个矩阵，找到从左上到右下的最小和路径。
思路：
1.在原矩阵基础上进行操作即可，首先分别处理行和列，从1开始当前位等于当前值加上前一位的值
2.除了第一行第一列的值以外，其余各点的值等于本身值加上 其上和其左之间的较小值
3.返回矩阵右下角的坐标的值即可
注意：
1.因为[0][0]不变，所以所有的循环都从1开始
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for(int i = 1; i< m;++i) grid [i][0] += grid[i-1][0];
        for(int j = 1; j< n;++j) grid [0][j] += grid[0][j-1];
        for(int i = 1;i < m; ++i){
            for(int j = 1; j < n; ++j){
                grid[i][j] = min(grid[i][j]+grid[i-1][j],grid[i][j]+grid[i][j-1]);
            }
        }
        return grid[m-1][n-1];
    }
};

二刷：
注意DP的问题能在远数组基础上修改就不要新建一个vector，初始化和边界容易出错。
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for(int i = 1; i < m; ++i) grid[i][0] +=grid[i-1][0];
        for(int j = 1; j < n; ++j) grid[0][j] += grid[0][j-1];
        for(int i = 1; i < m ;++ i){
            for(int j = 1; j < n; ++j){
                grid[i][j] = min(grid[i-1][j]+grid[i][j], grid[i][j-1] + grid[i][j]);
            }
        }
        return grid[m-1][n-1];
        
    }
};