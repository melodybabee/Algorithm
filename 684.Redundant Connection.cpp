题意：删除无向图中的环使得其成为树
方法一：递归DFS
思路：
1.因为是无向图，所以建立一个邻接表来形成这张图，每当插入一条新的边之前，判断是否会形成环，如果形成环，直接返回这条边。不成环就插入邻接表。
题目中说的有很多种情况的时候返回坐标位置靠后的，也就是最后一条形成环的边，和思路正好满足。
2.判断是否成环建立起始位置，终点位置，邻接表的递归，为了避免形成1-2，2-1的死环，用一个变量记录下之前的位置。
如果起始位置等于终点位置，那么成环，返回true
对起始位置在map中进行查找，如果等于之前的位置，跳过；再更新起始位置终点位置进行递归。
如果最后没有找到，返回false。
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        unordered_map<int,unordered_set<int>>map;
        for(auto e : edges){
            if(hascycle(e[0],e[1],map,-1)) return e;
            map[e[0]].insert(e[1]);
            map[e[1]].insert(e[0]);
        }
        return {};
    }
    bool hascycle(int start, int target,unordered_map<int,unordered_set<int>>&map,int pre){
        if(map[start].count(target)) return true;
        for(auto a : map[start]){
            if(a == pre) continue;
            if(hascycle(a,target,map,start)) return true;
        }
        return false;
    }
};
方法2:BFS遍历
思路：
1.同样对每一条边进行遍历，queue中放第一个结点的位置即可。通过queue进行BFS查找，用一个set来记录是否已经遍历过这条边。
2.每遍历一条边进入while循环判断是否有环，只要能在map中找到就是有环。再把map中对应的结点依次放入queue。
3.如果不成环那么就直接在map中插入边的对应关系
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        unordered_map<int,unordered_set<int>>map;
        for(auto e : edges){
            queue<int>q{{e[0]}};
            unordered_set<int>s{{e[0]}};
            while(!q.empty()){
                int temp = q.front();
                q.pop();
                if(map[temp].count(e[1])) return {e[0],e[1]};
                for(int m : map[temp]){
                    if(s.count(m)) continue;
                    q.push(m);
                    s.insert(m);
                }
            }
            map[e[0]].insert(e[1]);
            map[e[1]].insert(e[0]);
        }
        return {};
    }
};
方法3:union find
思路：
1.建立一个数组用来记录union find,因为题目中给说了最多1000个点，那么最多不一样的有2000个，设置成2001就可以
也可以按照edge大小构造
2.遍历结点，依次找到每一个结点的根结点的位置，如果相等，表示有环，直接返回，不等，把他们连在一起，连在相同过的根下面
3.找根的过程就是如果没有出现过这个结点，那么直接返回，自己是自己的根
如果不等于-1，如果自己等于自己，直接返回；否则递归查找知道找到自己等于等于的位置，是该点的根结点。
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int>vec(2001,-1);
        for(auto e : edges){
            int root1 = findroot(vec,e[0]);
            int root2 = findroot(vec,e[1]);
            if(root1 == root2) return e;
            else  vec[root1] = root2;
        }
        return {};
    }
    int findroot(vector<int>&vec, int node){
        if(vec[node] == -1) return node;
        else{
            if(vec[node] == node) return node;
            else return findroot(vec,vec[node]);
        }
    }
};

解题过程：
input: arrays
every node has formed an edge 
output:
node, 1st form a graph

method 1:
1 - 2 - 3 - 1
same root : cycle
not root: combine it to each other
node: root
1 : 1
2 : 1
3 : 1


node : root 
1 : 1
2 : 1
3 : 1
4 : 1

1.make a loop to each node and to find their root
2.if they have the same root, output
otherwise, combine it to each other

vector<int> deleteloop(vector<vector<int>> & edges){
    vector<int>vec(2001,-1);
    for(auto e : edges){
        int root1 = findroot(vec,e[0]);
        int root2 = findroot(vec,e[1]);
        if(root1 == root2) return e;
        else  vec[root1] = root2;
    }
    return {};
}

int findroot(vector<int>&vec, int node){
    if(vec[node] == -1) return node;
    else{
        if(vec[node] == node) return node;
        else return findroot(vec,vec[node]);
    }
}

[[1,2], [1,3], [2,3]]1
1 : 1
2 : 1
3 : 1


