题意：求汇率问题，给出一了若干组除数和被除数及其商，求出任意一个包括他们的组合，如果没有返回-1
方法一：DFS + graph
T(n) = e + q*e
S(n) = e;
e表示结点的个数，q表示所有的路径，如果每条路径都要从起点开始的话就是q*e
思路：
1.首先因为给出的是一组一组的数据，那么可以把题目中的信息转换为一个有向加权重的图。
每一组数据的原始值表示从A到B的方向，同时在图的邻接矩阵中插入权重值。同时计算出反向的从B到A的权重，输入到邻接矩阵中。
2.开始遍历目标数组，判断目标数组中的两个元素是否都在邻接矩阵中，如果不在，直接在结果数据中插入-1.0
3.如果存在，那么从这个点开始进行DFS遍历，因为是联通的原因，需要建立一个visited数组来判断是否遍历过每个元素，因为涉及到查找的功能，此处用set来判断，可去重
4.DFS的终止条件是如果当当前结点的第一个位置与第二个位置重合了，那么就直接返回1.0
5.遍历到一个新的点在set中插入，对以此元素开头的矩阵行进行遍历，如果遍历过某个数字，那么直接跳过
没有的话以这个新的点为标准进行dfs遍历，如果能够找到目标位置，说明有路径从起始位置到终点，那么计算路径长度，是第二段的长度的返回值乘上邻接矩阵中的横纵坐标值
没有路径返回-1.0
注意：
1.构造邻接矩阵的方法是建立一个unordered_map，key放入数字/字符，value部分还是一个unordered_map
2.在遍历的过程中，auto i : g[a]其中i的形式是一个unordered_map的形式，在unordered_map取key位置的元素需要用i.first
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        vector<double>ans;
        unordered_map<string,unordered_map<string,double>>g;
        for(int i = 0; i < equations.size();++i){
            g[equations[i].first][equations[i].second] = values[i];
            g[equations[i].second][equations[i].first] = 1/values[i];
        }
        for(auto q: queries){
            if(!g.count(q.first) || !g.count(q.second)){
                ans.push_back(-1.0);
                continue;
            }
            unordered_set<string>set;
            ans.push_back(dfs(q.first,q.second,g,set));
        }
        return ans;
    }
    
    double dfs(string a, string b,unordered_map<string,unordered_map<string,double>>&g,unordered_set<string>&set){
        if(a == b) return 1.0;
        set.insert(a);
        for(auto i : g[a]){
            string temp = i.first;
            if(set.count(temp)) continue;
            double ret = dfs(temp,b,g,set);
            if(ret > 0) return ret * g[a][temp];
        }
        return -1.0;
    }
};
方法2:union find
思路：
1.利用并查集的核心思想是把根结点相同的所有结点挂在相同的根下
2.那么首先建立一个unordered_map，key用来放每个坐标，value位置放入一对pair,pair.first表示这个结点的根结点，pair.second表示这个结点与其根节点的关系。
此处至于因为都是以根结点为基础的，因此在value中取到的k值是指当前结点是k倍的根结点
而如果需要反转的话，那么根结点表示1/k的当前结点
3.把原始数组中的每一个结点位置放在map中，都不存在就直接插入，如果有一方存在就按照关系进行连接
如果都存在，找到两个结点的根结点，第一个值的根结点在map中的映射等于第二个值的根结点，关系等于此处的k值除以第一个数字的关系再乘上第二个数字的关系
注意运算顺序k / x.second * y.second
4.在map中用递归查找一个数字的根结点，如果它的根结点不是其在map中映射的它本身，说明没有到根结点，那么继续向前寻找，直到找到
5.遍历query,如果其中一方不存在，那么直接返回-1.0,如果根结点不同，返回-1.0,否则返回相除的结果
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string,pair<string,double>>parents;
        vector<double>ans;
        for(int i = 0 ; i < equations.size(); ++i){
            string a = equations[i].first;
            string b = equations[i].second;
            double k = values[i];
            if(!parents.count(a) && !parents.count(b)){
                parents[a] = {b,k};
                parents[b] = {b,1.0};
            }else if(!parents.count(a)){
                parents[a] = {b,k};
            }else if(!parents.count(b)){
                parents[b] = {a,1.0/k};
            }else{
                auto x = find(a,parents);
                auto y = find(b,parents);
                parents[x.first] = {y.first, k / x.second * y.second};
            }
        }
        for(auto q : queries){
            string a = q.first;
            string b = q.second;
            if(!parents.count(a) || !parents.count(b)) 
            {
                ans.push_back(-1.0);
                continue;
            }
            auto x = find(a,parents);
            auto y = find(b,parents);
            if(x.first != y.first) ans.push_back(-1.0);
            else ans.push_back(x.second/y.second);
        }
        return ans;
        
    }
    pair<string, double> find(string a,unordered_map<string,pair<string,double>>&parents){
        if(a != parents[a].first){
            auto p = find(parents[a].first, parents);
            parents[a].first = p.first;
            parents[a].second *= p.second;
        }
        return parents[a];
    }
    
};