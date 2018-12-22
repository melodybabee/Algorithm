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