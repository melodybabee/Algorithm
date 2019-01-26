题意：找最小高度树
思路：
1.本题实际上是在无向图中找到根结点，这个根结点到任意结点的路径能够保持最小值
2.首先建立一个图，因为不需要知道每个结点连接的结点的顺序，为了方便插入，直接用一个unordered_set就可以
因为是无向图，因此需要正反两个方向进行插入
3.利用剥洋葱的思路，首先把只连接一个结点的结点入队列，遍历这些结点在set中的值，在对应的值中删除掉这个结点
如果删除之后某个节点也只连接一个点了，那么入队列
4.最后在栈中会剩下1到2个结点，跳出while循环，在结果数组中插入队列中的结点，返回结果
注意：
1.只要初始的结点数大于2，那么就进入队列。因为结点之间都是两两连接的，所以最后的结点数量只会是1或者2，如果有第三个点那么可以简化为1
每次进入队列之后记录下当前队列中的结点数量，再用总结点数减去这个数字，再开始遍历
2.如果只有一个结点，那么返回0
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if(n == 1) return {0};
        vector<unordered_set<int>>vec(n);
        queue<int>q;
        vector<int>ret;
        for(auto e : edges){
            vec[e.first].insert(e.second);
            vec[e.second].insert(e.first);
        }
        for(int i = 0; i < vec.size();++i){
            if(vec[i].size() == 1) q.push(i);
        }
        while(n > 2){
            int s = q.size();
            n -= s;
            for(int i = 0; i < s; ++i){
                int temp = q.front();
                q.pop();
                for(auto t : vec[temp]){
                    vec[t].erase(temp);
                    if(vec[t].size() == 1) q.push(t);
                }
            }
        }
        while(!q.empty()){
            ret.push_back(q.front());
            q.pop();
        }
        return ret;
    }
};
