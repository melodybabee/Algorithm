题意：判断飞机停指定站从起始位置到终点的最短距离。
方法一：graph+DFS
思路：
1.本题的问题本身是一个有序图的遍历问题，那么首先需要建图，根据给出的航线和距离更新邻接矩阵
2.进入DFS遍历，需要邻接矩阵，起始位置，终点位置，一个set集判断走过哪些点，临时记录的结果和返回的结果
3.在递归过程中，如果起点位置和终点位置相同，那么直接把临时的结果作为最终结果返回
如果循环的次数k小于0，那么也直接返回
4.最后在map中进入遍历。首先判断是否循环过，循环过或者当前的结果要大于之前的结果值，那么直接进行剪枝操作
5.在set中插入当前元素，进入DFS递归，当次递归之后要把元素从set中取出，用set.erase()方法
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        unordered_map<int,vector<vector<int>>>map;
        unordered_set<int>set{{src}};
        int res = INT_MAX;
        for(int i = 0; i < flights.size(); ++i){
            map[flights[i][0]].push_back({flights[i][1],flights[i][2]});
        }
        dfs(map,0,K,src,dst,set,res);
        return res == INT_MAX ? -1 : res;
        
    }
    
    void dfs(unordered_map<int,vector<vector<int>>>&map, int t, int k, int cur, int dst,unordered_set<int>&set, int &res){
        if(cur == dst) {
            res = t;
            return;
        }
        if(k < 0) return;
        for(auto a : map[cur]){
            if(set.count(a[0]) || t + a[1] > res) continue;
            set.insert(a[0]);
            dfs(map,t + a[1],k-1,a[0],dst,set,res);
            set.erase(a[0]);
        }
    }
};
方法2:graph + BFS
思路：
1.建图的方法与之前完全一样，还需要建立一个队列来进行BFS遍历
2.注意BFS通常用队列来表示，判断条件是while循环同时队列不为空的时候
3.每次遍历之前都需要记录下当前队列中的个数，为了便于计算，最好总大到小，也就是最大到0进行递减。
每次取第一个值，如果等于终止值，计算较小的结果，再以这一点为基准进行循环遍历，如果计算过程中的值大于结果，直接舍弃
如果满足条件，那么重新放入队列
4.每次结束内部的循环之后计数，如果大于K，那么跳出while循环
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        unordered_map<int,vector<vector<int>>>map;
        queue<vector<int>>q{{{src,0}}};
        int ret = INT_MAX;
        int count = 0;
        for(int i = 0; i < flights.size(); ++i){
            map[flights[i][0]].push_back({flights[i][1],flights[i][2]});
        }
        while(!q.empty()){
            for(int i = q.size(); i > 0 ; --i){
                auto temp = q.front();
                q.pop();
                if(temp[0] == dst) ret = min(ret,temp[1]);
                for(auto m : map[temp[0]]){
                    if(temp[1] + m[1] > ret) continue;
                    q.push({m[0],temp[1] + m[1]});
                }
            }
            if(count++ > K) break;
        }
        return ret == INT_MAX?-1 : ret;
    }
};
方法3:Bellman Ford求最短路径，松弛操作
思路：
1.松弛操作的过程也就是进行DP动态转移方程的过程
2.用一个dp[i][j]表示飞行i次飞到j的最少花费是多少
3.每次遍历从起点开始都设置初始值为0，自动遍历飞行表，更新每个行程的到达地，对其本身和到达它的起点+该段路程的花费之间取较小
4.最后返回飞行规定次数和到达目的地之后的值
注意：
1.因为dp数组从0开始，所以返回的结果是K+1为横坐标
2.如果想取非常大的话，可以设置为1e9,表示1*10的9次幂
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<vector<int>>dp(K+2,vector<int>(n,1e9));
        dp[0][src] = 0;
        for(int i = 1; i <= K+1; ++i){
            dp[i][src] = 0;
            for(auto f : flights){
                dp[i][f[1]] = min(dp[i][f[1]], dp[i-1][f[0]] + f[2]);
            }
        }
        return dp[K+1][dst] == 1e9 ? -1 : dp[K+1][dst];
    }
};