题意：判断无向图是否是有效的树
方法一：union find
思路：
1.判断无向图是否是树，首先要看有没有环，如果有环，直接返回false
其次还要看所有的结点是否能找到一个唯一的根，如果找到了，才是有效的树
2.那么建立一个数组用来记录union find,判断是否有环，最后还要看这个数组中的值是不是只有一个等于本身，表示这一点是根结点，如果是返回true
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        vector<int>vec;
        for(int i = 0; i < n; ++i){
            vec.push_back(i);
        }
        for(auto e :edges){
            int root1 = findroot(vec,e.first);
            int root2 = findroot(vec,e.second);
            if(root1 == root2) return false;
            vec[root2] = root1;
        }
        int temp = 0;
        for(int i = 0; i < vec.size(); ++i){
            if(vec[i] == i) ++temp;
        }
        return temp == 1;
    }
    
    int findroot(vector<int>&vec,int p){
        return vec[p] == p ? p : findroot(vec, vec[p]);
    }
};
优化：
利用结点数量和边的数量来做判断，结点数要是边的数量+1就能满足树
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        vector<int>vec;
        for(int i = 0; i < n; ++i){
            vec.push_back(i);
        }
        for(auto e :edges){
            int root1 = findroot(vec,e.first);
            int root2 = findroot(vec,e.second);
            if(root1 == root2) return false;
            vec[root2] = root1;
        }
        return edges.size() == n-1;
    }
    
    int findroot(vector<int>&vec,int p){
        return vec[p] == p ? p : findroot(vec, vec[p]);
    }
};
方法2:DFS
思路：
1.DFS首先需要用哈希表来构造图，同时需要一个vistied数组避免重复的遍历
2.从起点开始遍历，因为本题结点的范围是从0到n-1，因此按照visited数组的顺序遍历即可。
需要用一个pre来标记避免重复遍历
3.进入dfs之后，如果遍历过该点，直接返回false,否则在邻接表中递归遍历它所对应的元素
4.最后判断是否所有的结点都能遍历到形成联通图即可
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        unordered_map<int,unordered_set<int>>map;
        for(auto e : edges){
            map[e.first].insert(e.second);
            map[e.second].insert(e.first);
        }
        vector<bool>visited(n,false);
        if(!dfs(map,visited,0,-1)) return false;
        for(auto v: visited){
            if(v == false) return false;
        }
        return true;
    }
    
    bool dfs(unordered_map<int,unordered_set<int>>&map,vector<bool>&visited, int cur, int pre){
        if(visited[cur]) return false;
        visited[cur] = true;
        for(auto m : map[cur]){
            if(m != pre){
                if(!dfs(map,visited,m,cur)) return false;
            }
        }
        return true;
    }
};
方法3:BFS
思路：
1.在BFS中同样需要先构造图，接着用一个queue来进行BFS遍历
2.为了避免出现重复遍历相同元素的情况，要建立一个set来记录遍历到了哪些结点
3.每次进入while循环之后，遍历邻接矩阵，如果在set中表示遍历过，返回false,没有遍历过就一次入队列
同时注意要在这一点为key的邻接矩阵中删除之前的key,避免出现1-2，2-1的情况
4.最后判断set中的结点个数是否与结点数相同
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        unordered_map<int,unordered_set<int>>map;
        set<int>s{{0}};
        queue<int>q{{0}};
        for(auto e : edges){
            map[e.first].insert(e.second);
            map[e.second].insert(e.first);
        }
        while(!q.empty()){
            int temp = q.front();
            q.pop();
            for(auto m : map[temp]){
                if(s.count(m)) return false;
                q.push(m);
                s.insert(m);
                map[m].erase(temp);
            }
        }
        return s.size() == n;
    }
};