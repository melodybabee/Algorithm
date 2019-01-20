题意：遍历数组中所有为0的点，问从起始位置到结束位置有几条路径。
这道题的思路在contest中已经成形了，觉得可能过于复杂时间不够就没敢写，实在可惜！
思路：
1.因为本题的特点是需要把所有为0的点都走过来，因此建立一个双层循环，统计为0的点的个数，记录下起始位置和结束位置。
2.用dfs遍历回溯，从起始位置开始，向四个方向进行上下左右DFS递归/
递归的边界条件是，如果坐标等于终点且为0的计数器的数值结果为0，那么结果计数器+1
如果超出了边界范围，直接返回
3.每遍历到一个数字都更新数组中的值为0，避免重复递归某一个数字。回溯结束之后需要把为0的个数+1，同时数组中的值更新为0
class Solution {
private:
    int ret = 0;
    int empty = 1;
    int initx, inity,exitx,exity;
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        for(int i = 0; i < grid.size(); ++i){
            for(int j = 0; j < grid[0].size(); ++j){
                if(grid[i][j] == 0) ++empty;
                else if(grid[i][j] == 1){
                    initx = i;
                    inity = j;
                }else if(grid[i][j] == 2){
                    exitx = i;
                    exity = j;
                }
            }
        }
        dfs(initx,inity,grid);
        return ret;
    }
    
    void dfs(int i,int j,vector<vector<int>>& grid){
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] < 0) return;
        if(i == exitx && j == exity && empty == 0) {
            ++ret;
            return;
        }
        grid[i][j] = -1;
        --empty;
        dfs(i-1,j,grid);
        dfs(i+1,j,grid);
        dfs(i,j-1,grid);
        dfs(i,j+1,grid);
        grid[i][j] = 0;
        ++empty;
    }
};