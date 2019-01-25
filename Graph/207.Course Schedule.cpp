题意：
判断给出的课程表是否能够上完所有的课。（判断有向图中是否有环）
方法一：BFS
思路：
1.首先根据题目中的要求，如果所有的课程中有一个或者多个成环，那么就不能上完所有的课。因此就是有向图中判断是否有环的问题。
2.BFS的思想是从一个入度为0的结点开始入栈遍历，遍历它所有相连的结点，相连的结点入度值减1，再将入度为0的结点入队列。
3.因此需要建立一个二维数组来表示每个结点所相连的所有结点。
需要一个一维数组来记录每个结点有几个入度，依次遍历所连接的结点，从而形成BFS的思路。
再利用一个队列放入所有入度为0的点，每次循环到的新的位置结点入度-1，如果减为0了，那么就直接进入队列。
4.在队列不为空的时候一直进行循环，如果当队列为空的时候，在一维数组中仍然存在入度不为0的结点，那么说明有环，返回false
如果所有结点入度为0，那么返回true
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int>visited(numCourses,0);
        vector<vector<int>>graph(numCourses,vector<int>(0));
        queue<int>q;
        for(auto it:prerequisites){
            graph[it.second].push_back(it.first);
            ++visited[it.first];
        }
        for(int i = 0; i < visited.size();++i){
            if(visited[i]==0) q.push(i);
        }
        while(!q.empty()){
            int temp = q.front();
            q.pop();
            for(auto a:graph[temp]){
                --visited[a];
                if(visited[a] == 0)q.push(a);
            }
        }
        for(auto v : visited){
            if(v != 0) return false;
        }
        return true;
    }
};

方法2:DFS
1.首先利用原有的pair数组生成一个图，图的表示形式是vector中包含的set结构
2.分别设置两个数组用来判断遍历到的结点是否已经遍历过，visit表示开始的结点，onpath表示路径上的结点
在主函数中进行循环，在DFS函数中进行DFS遍历
3.一旦成环，就返回false,最后返回true
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>>graph = make_graph(numCourses,prerequisites);
        vector<bool>visited(numCourses,false);
        vector<bool>onpath(numCourses,false);
        for(int i = 0; i< numCourses;++i){
            if(!visited[i] && dfs(i,graph,onpath,visited)){
                return false;
            }
        }
        return true;
    }
    
    vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>>& prerequisites){
        vector<unordered_set<int>>graph(numCourses);
        for(auto p : prerequisites){
            graph[p.second].insert(p.first);
        }
        return graph;
    }
    
    bool dfs(int node,vector<unordered_set<int>>&graph,vector<bool>&onpath,vector<bool>&visited){
        if(visited[node]) return false;
        onpath[node] = visited[node]= true;
        for(auto n : graph[node]){
            if(onpath[n] ||dfs(n,graph,onpath,visited)) return true;
        }
        return onpath[node] = false;
    }
};

1.25复习
DFS
注意：
1.可以利用unordered_map建图，可以形成套路，但是需要注意value部分放的是set类型，遍历查找
2.要把先修课放到key的位置上，value的位置放入先修课后面的课程
3.在主函数中进入DFS判断，如果没有遍历到该点，才能够进入DFS遍历，如果遍历过该点那么直接跳过。当DFS返回true的时候，主函数返回false
4.【需要注意】进入DFS遍历后，开始从map对应的每一点上进行循环,如果遍历过这个点，或者DFS返回了true,那么最后需要返回false
如果满足不成环的条件，那么需要返回false
5.因为题目中给了条件是0 to n-1，因此visited和path数组设置成numCourses大小即可，同时从0开始循环
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        unordered_map<int,set<int>>map;
        for(int i = 0; i < prerequisites.size();++i){
            map[prerequisites[i].second].insert(prerequisites[i].first);
        }
        vector<bool>visited(numCourses,false);
        vector<bool>path(numCourses,false);
        for(int i = 0; i < numCourses; ++i){
            if(!visited[i] && dfs(i,map,visited,path)){
                return false;
            }
        }
        return true;
    }
    
    bool dfs(int i, unordered_map<int,set<int>>&map,vector<bool>&visited, vector<bool>&path){
        if(visited[i]) return false;
        path[i] = visited[i] = true;
        for(auto m : map[i]){
            if(path[m] || dfs(m,map,visited,path)) return true;
        }
        path[i] = false;
        return false;
    }
};
注意BFS的思想是判断所有结点的入度是否为0，为0表示没有先修课，那么入栈，从它开始循环。
每遍历到一个点把他们的入度-1，所有入度为0的点入栈，最后判断当栈为空的时候是否所有点的入度都是0，如果不是，那么直接返回false.