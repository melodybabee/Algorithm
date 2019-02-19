题意：490follow up,找到迷宫中的最短路径
方法一：BFS
思路：
1.因为需要求出最短路径，所以BFS的方法要比DFS的方法更加直接，一层一层向外扩展更新即可
那么需要一个二维数组用来更新路径值，起点位置为0，默认为INT_MAX，最后返回终点位置的值。
2.通过queue的方法进行更新，每次取出队列顶部的元素和它在二维数组中对应的值，每次没有到边上，对应的值+1
到了边上之后如果对应的值要比之前的值小，那么更新。如果没有到结尾，那么重新入栈
3.最后当队列为空的时候判断结尾位置上是否为INT_MAX，如果不是返回结果值。
class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        vector<vector<int>>dp(maze.size(), vector<int>(maze[0].size(),INT_MAX));
        dp[start[0]][start[1]] = 0;
        vector<vector<int>>dir{{0,1},{0,-1},{1,0},{-1,0}};
        queue<pair<int,int>>q;
        q.push({start[0],start[1]});
        while(!q.empty()){
            auto it = q.front();
            q.pop();
            for(int i = 0 ; i < dir.size();++i){
                int x = it.first;
                int y = it.second;
                int temp = dp[x][y];
                while(x >= 0 && y >= 0 && x < maze.size() && y < maze[0].size() && maze[x][y] == 0){
                    x += dir[i][0];
                    y += dir[i][1];
                    ++temp;
                }
                x -= dir[i][0];
                y -= dir[i][1];
                --temp;
                 if(temp < dp[x][y]){
                     dp[x][y] = temp;
                     if(x != destination[0] || y != destination[1]) q.push({x,y});
                 }
            }
        }
        int res = dp[destination[0]][destination[1]];
        return res == INT_MAX ? -1: res;
    }
};

优化：Dijkstra Algorithm最短路径方法
思路：
1.Dijkstra Algorithm最短路径方法适用于有向权重图中的单源最短路径，可以把起点位置看作单源，那么逐渐进行松弛操作
2.利用优先队列根据第三个变量作为距离，从距离近的位置开始比较，如果当前位置上的值已经小于优先队列头部的值，那么剪枝操作就直接跳过
注意：
priority_queue需要用q.top()出栈
自定义排序方法： priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)>q(cmp);
auto cmp = [](vector<int>&a, vector<int>&b){
            return a[2] > b[2];
        };
补充：
c++11特性，auto、decltype，Lambda.
decltype与auto关键字一样，用于进行编译时类型推导，不过它与auto还是有一些区别的。decltype的类型推导并不是像auto一样是从变量声明的初始化表达式获得变量的类型，而是总是以一个普通表达式作为参数，返回该表达式的类型,而且decltype并不会对表达式进行求值。
其实Lambda表达式就是匿名函数（annoymous function）——允许我们使用一个函数，但不需要给这个函数起名字。
类似[](int &a, int &b)->bool {
         return a > b;
}
的形式。
class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        vector<vector<int>>dp(maze.size(), vector<int>(maze[0].size(),INT_MAX));
        dp[start[0]][start[1]] = 0;
        vector<vector<int>>dir{{0,1},{0,-1},{1,0},{-1,0}};
        auto cmp = [](vector<int>&a, vector<int>&b){
            return a[2] > b[2];
        };
        priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)>q(cmp);
        q.push({start[0],start[1],0});
        while(!q.empty()){
            auto it = q.top();
            q.pop();
            if(dp[it[0]][it[1]] < it[2]) continue;
            for(int i = 0 ; i < dir.size();++i){
                int x = it[0];
                int y = it[1];
                int temp = dp[x][y];
                while(x >= 0 && y >= 0 && x < maze.size() && y < maze[0].size() && maze[x][y] == 0){
                    x += dir[i][0];
                    y += dir[i][1];
                    ++temp;
                }
                x -= dir[i][0];
                y -= dir[i][1];
                --temp;
                 if(temp < dp[x][y]){
                     dp[x][y] = temp;
                     if(x != destination[0] || y != destination[1]) q.push({x,y,temp});
                 }
            }
        }
        int res = dp[destination[0]][destination[1]];
        return res == INT_MAX ? -1: res;
    }
};
