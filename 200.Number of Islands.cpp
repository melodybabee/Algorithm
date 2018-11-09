题意：
在数组中连续的1的位置为一个岛屿，找到一共有几个岛屿。
方法一：DFS递归
T(n) = O(M*N); S(n) = O(M*N);
思路：
1.dfs遍历整个数组，如果有1，递归看它的上下左右是否有1，有则继续，如果判断结束所有连续的位置没有1，返回主函数，岛屿数量+1.
2.需要用一个flag数组记录下是否遍历过该位置，每遍历过一次就置为true,如果遍历过，在下一次遍历的时候就应该跳过，数组一共被遍历一次。
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        vector<vector<bool>> flag (m, vector<bool>(n,false));
        for(int i = 0; i < m ;++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j] == '1' && flag[i][j] == false){
                    dfs(grid,flag,i,j);
                    ++res;
                }
            }
        }
        return res;
    }
    
    void dfs(vector<vector<char>>& grid,vector<vector<bool>>&flag,int i, int j){
        if(i < 0 || i >= grid.size()) return;
        if(j < 0 || j >= grid[0].size()) return;
        if(grid[i][j] != '1' || flag[i][j]) return;
        flag[i][j] = true;
        dfs(grid,flag,i+1,j);
        dfs(grid,flag,i-1,j);
        dfs(grid,flag,i,j+1);
        dfs(grid,flag,i,j-1);
    }
};
方法二：BFS
T(n) = O(M*N); S(n) = O(min(M,N));
because in worst case where the grid is filled with lands, the size of queue can grow up to min(M,N).
思路：
1.在遍历的时候和DFS一样，只不过递归时，DFS是直接从一边的结点连续深入，而BFS是从一个结点的四周开始寻找。
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        for(int i = 0; i < m ;++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j] == '1' ){
                    bfs(grid,i,j);
                    ++res;
                }
            }
        }
        return res;
    }
    
    void bfs(vector<vector<char>>& grid,int x, int y){
        queue<vector<int>> q;
        q.push({x,y});
        grid[x][y] = '0';
        while(!q.empty()){
            x = q.front()[0];
            y = q.front()[1];
            q.pop();
            if(x > 0 && grid[x-1][y] == '1'){
                q.push({x-1,y});
                grid[x-1][y] = '0';
            }
            if(y > 0 && grid[x][y-1] == '1'){
                q.push({x,y-1});
                grid[x][y-1] = '0';
            }
            if(x < grid.size()-1 && grid[x+1][y] == '1'){
                q.push({x+1,y});
                grid[x+1][y] = '0';
            }
            if(y < grid[0].size()-1 && grid[x][y+1] == '1'){
                q.push({x,y+1});
                grid[x][y+1] = '0';
            }
        }
    }
};
方法三：Union Find【待学习】