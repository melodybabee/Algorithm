题意：找无向图中有几个连通的部分
方法一：union find
思路：
1.首先把标记连通图的数组设置为坐标本身，开始找到每个位置的根，如果相同，跳过，不相同的话把他们连接在一起
2.再次遍历数组，如果数组中的数值仍然等于其本身，那么表示这个点是根结点。计数器+1
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        vector<int>ret(n);
        for(int i = 0 ; i < n; ++i){
            ret[i] = i;
        }
        for(auto e:edges){
            int root1 = findroot(e.first,ret);
            int root2 = findroot(e.second,ret);
            if(root1 == root2) continue;
            ret[root1] = root2;
        }
        int temp = 0;
        for(int i = 0; i < ret.size(); ++i){
            if(ret[i] == i){
                ++temp;
            }
        }
        return temp;
    }
    
    int findroot(int p, vector<int>&ret){
        return ret[p] == p ? p : findroot(ret[p],ret);
    }
};
方法2:DFS
思路：
1.先构造图，开始遍历每一个结点，如果没有访问过，说明到了一个新的连通区域，那么计数器+1
2.开始对这个结点进行DFS遍历，把与它相连接的所有结点都标记为true。
3.最后返回计数器。
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        unordered_map<int,unordered_set<int>>map;
        vector<bool>visited(n,false);
        int ans = 0;
        for(auto e : edges){
            map[e.first].insert(e.second);
            map[e.second].insert(e.first);
        }
        for(int i = 0;i < n; ++i){
            if(!visited[i]){
                ++ans;
                dfs(map,visited,i);
            }
        }
        return ans;
    }
    
    void dfs(unordered_map<int,unordered_set<int>>&map, vector<bool>&visited, int t){
        if(visited[t]) return;
        visited[t] = true;
        for(auto a : map[t]){
            dfs(map,visited,a);
        }
    }
};