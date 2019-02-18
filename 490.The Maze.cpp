题意：从起点位置走到终点并判断终点是否是停止的位置
方法一：DFS
思路：
1.题意中有两个要求，一个是需要从起点到达终点，一个是终点要满足不能继续滚动的条件。
2.那么建立一个DFS，需要一个set来记录所有走过的点，如果起点等于终点，那么直接返回true,因为都是数组的形式，所以直接比较数组即可
如果在set中查找到走过的点，那么直接返回false
因为题目中说到了起点位置和终点位置不在同一个位置,所以在DFS中的边界条件相等就返回true
3.注意还需要判断是否停止，那么对新的点进行DFS递归之前，判断它是否能到边上，如果可以，那么直接返回，如果不能，那么从这个点开始再进行递归查找,直到返回边界上的点。
class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination){
        set<vector<int>>s;
        return dfs(maze,start,destination,s);
    }
    
    bool dfs(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination,set<vector<int>>&s){
        if(start == destination) return true;
        if(s.find(start) != s.end()) return false;
        s.insert(start);
        vector<vector<int>>dirc{{0,1},{1,0},{-1,0},{0,-1}};
        for(int i = 0; i < dirc.size();++i){
            vector<int> temp = toend(maze,start,dirc[i]);
            if(temp == destination || dfs(maze,temp,destination,s)){
                return true;
            }
        }
        return false;
    }
    
    vector<int> toend(vector<vector<int>>& maze, vector<int>& start,vector<int>& dir){
        int x = start[0]+dir[0];
        int y = start[1]+dir[1];
        if(x < 0 || y < 0 || x == maze.size() || y == maze[0].size() || maze[x][y] == 1){
            return start;
        }
        vector<int> newvec = {x,y};
        return toend(maze,newvec,dir);
    }
};
方法2:BFS
思路：
1.BFS的方法要用到queue,先输入第一个结点，每次输出一个，对这个输出的结点进行四个方向的while循环，直到找到边界位置。
2.判断边界位置是否循环过，如果没有，入队列。
核心思想是判断所有的边界位置是否等于终点，如果不等于，那么返回false.
class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        vector<vector<int>> dir{{0,1},{0,-1},{1,0},{-1,0}};
        vector<vector<bool>> visited(maze.size(),vector<bool>(maze[0].size(),false));
        queue<pair<int,int>>q;
        q.push({start[0],start[1]});
        visited[start[0]][start[1]] = true;
        while(!q.empty()){
            auto it = q.front();
            q.pop();
            if(it.first == destination[0] && it.second == destination[1]) return true;
            for(auto d : dir){
                int x = it.first;
                int y = it.second;
                while(x >= 0 && y >= 0 && x < maze.size() && y < maze[0].size() && maze[x][y] == 0){
                    x += d[0];
                    y += d[1];
                }
                x -= d[0];
                y -= d[1];
                if(!visited[x][y]){
                    visited[x][y] = true;
                    q.push({x,y});
                }
            }
        }
        return false;
    }
};