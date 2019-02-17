题意：坏橘子可以互相传染，求出多少次所有的橘子都会被传染上
思路：
1.首先把所有的坏橘子入队列，利用BFS，每次输出一个坏橘子，判断它周围上下左右的位置上是否有好的橘子，只要有就会被传染上，那么入队列
2.每次循环队列进行一次计数，当队列为空的时候，如果还有橘子没有被传染上，那么返回-1；否则返回计数器的值
注意：
题目中的含义是如果有不被传染的橘子，那么返回-1。所以如果一开始就没有好橘子，那么返回0，如果都是好橘子，返回-1.所以在进入队列之前需要单独判断一下
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int,int>>q;
        int count = 0;
        int temp = 0;
        vector<pair<int,int>>dir{{0,1},{0,-1},{1,0},{-1,0}};
        for(int i = 0; i < grid.size(); ++i){
            for(int j = 0; j < grid[0].size(); ++j){
                if(grid[i][j] == 2){
                    q.push({i,j});
                }
                if(grid[i][j] == 1) ++temp;
            }
        }
        if(q.empty() && temp == 0) return 0;
        while(!q.empty()){
            int num = q.size();
            ++count;
            for(int i = 0; i < num; ++i){
                auto it = q.front();
                int xx = it.first;
                int yy = it.second;
                q.pop();
                for(int k = 0;k < 4;++k){
                    if(xx +dir[k].first >= 0 && xx +dir[k].first < grid.size() && yy+dir[k].second >= 0 && yy+dir[k].second < grid[0].size() && grid[xx +dir[k].first][yy +dir[k].second] == 1){
                        q.push({it.first +dir[k].first,it.second +dir[k].second});
                        grid[xx +dir[k].first][yy +dir[k].second] = 2;
                    }
                }
            }
            
        }
        for(int i = 0; i < grid.size(); ++i){
            for(int j = 0; j < grid[0].size(); ++j){
                if(grid[i][j] == 1){
                    return -1;
                }
            }
        }
        return count-1;
    }
};