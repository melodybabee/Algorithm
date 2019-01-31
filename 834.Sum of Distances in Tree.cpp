题意：
找到树中每个结点到其他所有结点的路径总和。
思路：
1.先用一个图记录下各个结点之间的连接关系
2.设置一个数组来记录每个点上的子树结点有多少个，还有一个dp数组来记录当前位置的结点到左右结点的值是多少
还需要两个数组对两次DFS分别记录遍历过哪些结点，避免重复遍历
3.第一轮DFS首先从根结点开始，更新以每个根结点为起始位置，到所有结点的路径和的值，如果没有子结点，那么在计数数组中+1
dp[i]表示以i为根，到他的子结点的所有路径和。动态转移方程是当前根结点的值=它的子结点的值+子结点的个数*1，1表示从根结点到子结点的路径，一共有n个子结点，因此要n*1
4.第二轮DFS用来处理从各个子结点出发到各个结点的距离
首先更新距离的方程是，当前结点的值=其根结点的值-子结点的个数+所有结点的数量-子结点的个数
其根结点的值-子结点的个数表示的是它的根结点不算上它本身，到其他所有子结点的路径和，现在需要从当前结点到根结点，那么需要加上除了子结点自身数量以外，有几个结点走几次1
再对其子结点调用递归
5.最后返回结果
class Solution {
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        vector<unordered_set<int>>vec(N);
        for(auto e : edges){
            vec[e[0]].insert(e[1]);
            vec[e[1]].insert(e[0]);
        }
        unordered_set<int>s1;
        unordered_set<int>s2;
        vector<int>num(N);
        vector<int>value(N);
        dfs1(0,vec,s1,num,value);
        dfs2(0,vec,s2,num,value,N);
        return value;
    }
    
    void dfs1(int root,vector<unordered_set<int>>&vec,unordered_set<int>&s1,vector<int>&num,vector<int>&value){
        s1.insert(root);
        for(auto a : vec[root]){
            if(s1.count(a) == 0){
                dfs1(a,vec,s1,num,value);
                num[root] += num[a];
                value[root] += value[a] + num[a];
            }
        }
        ++num[root];
    }
    
    void dfs2(int root,vector<unordered_set<int>>&vec,unordered_set<int>&s2,vector<int>&num,vector<int>&value,int N){
        s2.insert(root);
        for(auto a : vec[root]){
            if(s2.count(a) == 0){
                value[a] = value[root] - num[a]+N-num[a];
                dfs2(a,vec,s2,num,value,N);
            }
        }
    }
};