题意：
去除二维数组中所有连接的结点，求出最多能够去除多少个结点。
方法一：union find
T（n）= O(nlogn);n是二维数组中数组对的个数，logn是指union find.
思路：
1.题意也可以转化为找到二维数组中独立存在的点，最后用总的结点数减去独立存在的点即为所有有连接的点。
2.所以用union find是最直接的方法，把左右能够连接的结点更新为统一的坐标值，那么结果即为所有没有没遍历到的值。
3.设置一个数组记录连接情况。遍历二维数组，如果数组中的两个值横坐标相等或者纵坐标相等，那么把它们连接起来。
4.在union的方法中，首先查找p中两个点的坐标是否相等，如果相等无需操作，如果不等，那么把前一个的坐标统一为后一个。
5.在查找方法中，查找p中的坐标值，如果为-1,那么返回当前值，如果不为-1，那么返回其所连接的值。
6.最后统计数组中-1的数量就是独立区域的值，如果在独立区域中，结果-1，最后返回结果。
注意：
1.因为有独立的结点，在连接的区域也会有一个顶点作为“独立”的结点，因此连接的区域中会有一个顶点的值也为-1。
比如二维数组中的所有顶点都相连，但是返回值为1，因为有一个点是顶点。
2.注意union方法需要别名，因为union方法在c++中有内置设定。
class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        if(stones.size() <= 1) return 0;
        int m = stones.size();
        vector<int> p (m,-1);
        for(int i = 0 ; i < m; ++i){
            for(int j = i+1; j < m ;++j){
                if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]){
                    u(p,i,j);
                }
            }
        }
        int res = m;
        for(auto a :p) {
            if(a == -1) --res;
        }
        return res;
    }
    
    void u(vector<int>&p, int i, int j){
        int px = find(p,i);
        int py = find(p,j);
        if(px != py){
            p[px] = py;
        }
    }
    
    int find(vector<int>&p, int index){
        if(p[index] == -1) return index;
        return find(p,p[index]);
    }
};
方法二：DFS
类似200找连接的岛屿。
思路：
1.首先根据题目中给出的二维数组的关系来更新为一个新的数组，如果有连接置为1。
2.开始调用DFS，如果其上下左右中有一个为1，那么表示连接，继续递归，没进入一次递归记录下当前连接的个数。
3.最后用总的个数减去所有有连接的结点个数即可。