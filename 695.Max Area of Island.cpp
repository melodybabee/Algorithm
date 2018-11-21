题意：
找到二维矩阵中连续的最多个1。
思路1:DFS
1.题目中的意思是找到最大的岛屿面积，即连续1最多的个数。因此就是基本的DFS/BFS思想
2.本题的不同之处在于要从一个起始为1的位置开始进行DFS，因此在主函数中需要有一个双层遍历。
但是如果每个数字都进行双层遍历的话时间复杂度会极高，因此只要找到一个1，相加后那么把这个位置更改为-1，这样就不会再次进入循环。
3.设置一个res作为最终返回的结果，每次取较大值。count每次进入循环的时候置为0，作为当次循环的计数器。
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int res = 0;
        for(int i = 0; i < grid.size(); ++i){
            for(int j = 0; j < grid[0].size();++j){
                if(grid[i][j] != 1) continue;
                int count = 0;
                helper(grid,i,j,count,res);
            }
        }
        return res;
    }
    
    void helper(vector<vector<int>>& grid,int i, int j, int &count, int &res){
        if(i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] != 1) return;
        ++count;
        res = max(res,count);
        grid[i][j] = -1;
        helper(grid,i+1,j,count,res);
        helper(grid,i,j+1,count,res);
        helper(grid,i-1,j,count,res);
        helper(grid,i,j-1,count,res);
    }
};
思路2:BFS
BFS模版：
1.首先设置一个变量记录下所要返回的结果和数组的长和宽。
2.开始循环二维数组，当不是1的时候跳过重新进入循环。遇到1之后开始计数，把第一对为1的坐标输入到queue中，并把这个坐标置为-1.
3.while queue不为空的时候，用一个auto输出头部坐标，表示有一个1，那么计数器+1，返回值取较大。
4.开始从这一点向四周扩展，设置auto变量，在开始需要设置一个四个方向的二维数组，用来做上下左右运算。
5.分别用x,y来对左边进行加和并判断，如果不满足要求，直接跳过；如果满足要求说明找到一个1，把原位置替换为-1，把当前坐标push到queue中。
class Solution {
public:
    vector<vector<int>> d{{1,0},{-1,0},{0,1},{0,-1}};
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        for(int i = 0; i < grid.size(); ++i){
            for(int j= 0; j < grid[0].size(); ++j){
                if(grid[i][j] != 1) continue;
                int count = 0;
                queue<pair<int,int>> q{{{i,j}}};
                grid[i][j] = -1;
                while(!q.empty()){
                    auto temp = q.front();
                    q.pop();
                    ++count;
                    res = max(res,count);
                    for(auto a : d){
                        int x = temp.first+a[0];
                        int y = temp.second+a[1];
                        if(x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 1)continue;
                        grid[x][y] = -1;
                        q.push({x,y});
                    }
                }  
            }
        }
        return res;
    }
};
