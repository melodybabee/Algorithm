题意：207 follow up,输出一条能够从头到尾上课的路径，没有的话返回空
方法一：DFS
思路：
1.同样需要建立一个图来记录每一个结点的位置，开始遍历，注意没有遍历过才能进入DFS，因此是!visited[i]
2.如果在DFS中返回的是true，表示有环，那么直接返回空数组
如果不是，那么就对记录结果的ans数组进行reverse()操作，把拓扑排序的反向输出
3.在DFS方法中需要判断是否有环，如果没有，同时到达了最后一个结点的位置，那么输入到结果数组中
注意：
1.拓扑排序是从入度为0的点开始的线性排列，因为DFS会首先找到最深的点，也就是最后一个位置上的点，因此最后需要反向。
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        unordered_map<int,set<int>>map;
        vector<bool>visited(numCourses,false);
        vector<bool>path(numCourses,false);
        vector<int>ans;
        for(auto p : prerequisites){
            map[p.second].insert(p.first);
        }
        for(int i = 0; i < visited.size(); ++i){
            if(!visited[i] && dfs(i,map,visited,path,ans)){
                return {};
            }
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
    
    bool dfs(int i, unordered_map<int,set<int>>&map,vector<bool>&visited,vector<bool>&path,vector<int>&ans){
        if(visited[i]) return false;
        path[i] = visited[i] = true;
        for(auto m : map[i]){
            if(path[m] || dfs(m,map,visited,path,ans)) return true;
        }
        ans.push_back(i);
        path[i] = false;
        return false;
    }
};
方法二：BFS
1.BFS方法的核心在于要找到入度为0的点，从这一点开始入栈进行判断
2.每进入循环一次就在结果数组中输出一个数字，最后判断visited数组中是否都是0，或者判断结果数组的长度是否等于visited数组
3.因为是从入度为0的点开始遍历的，所以自然就是拓扑排序的结果
注意：
遇到queue的一定要记得pop()!
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        unordered_map<int,set<int>>map;
        vector<int>visited(numCourses,0);
        vector<int>ans;
        queue<int>q;
        for(auto p : prerequisites){
            map[p.second].insert(p.first);
            ++visited[p.first];
        }
        for(int i = 0; i < visited.size(); ++i){
            if(visited[i] == 0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int temp = q.front();
            ans.push_back(temp);
            q.pop();
            for(auto m : map[temp]){
                --visited[m];
                if(visited[m] == 0) q.push(m);
            }
        }
        for(int v : visited){
            if(v != 0) return {};
        }
        return ans;
    }
    
};
补充：拓扑排序，只在有向无环图中出现
在图论中，拓扑排序（Topological Sorting）是一个有向无环图（DAG, Directed Acyclic Graph）的所有顶点的线性序列。且该序列必须满足下面两个条件：
每个顶点出现且只出现一次。
若存在一条从顶点 A 到顶点 B 的路径，那么在序列中顶点 A 出现在顶点 B 的前面。
有向无环图（DAG）才有拓扑排序，非DAG图没有拓扑排序一说。
如何写出一个图的拓扑排序：
(1)找入度为0的点。从 DAG 图中选择一个 没有前驱（即入度为0）的顶点并输出。
(2)从图中删除该顶点和所有以它为起点的有向边。
重复 1 和 2 直到当前的 DAG 图为空或当前图中不存在无前驱的顶点为止。后一种情况说明有向图中必然存在环。
通常，一个有向无环图可以有一个或多个拓扑排序序列。
