题意：684follow up,有向图删除一条边得到树
思路：
1.684的题目是找无向图有没有环，那么直接判断是否成环即可。
但是本题是有向图，那么会有三种不同的情况。
(1)没有环，但是会有入度为2的结点,删除形成入度为2的最后一条边
(2)有环，没有入度为2的结点，删除形成环的最后一条边
(3)有环，有入度为2的结点，删除组成环和入度为2的第一条边，因为形成环，环内不可能有入度为2的点，那么就要即形成环又入度为2的点，就是第一条边的位置
2.那么首先需要判断是否有入度为2的结点，即当前结点在之前是否出现过。
因为是有向图，因此找每条边上第二个结点的位置。如果有，那么把它之前的一条边记录下来，当前边为second
并把入度为2的点特殊标记，在找环的时候就不遍历这个点了
3.重新初始化union find数组，如果遇到之前入度为2的点，跳过。
union find判断是否有环，如果等，按照要求返回边或者第一条入度为2的边
如果不等，那么找到公共的根结点合并
4.最后如果没有环，那么返回入度为2的边
注意：
在标记入度为2的点的时候，因为需要在原有值的基础之上进行更改，因此auto遍历的时候需要用引用的形式。
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        vector<int>vec(2001,-1);
        vector<int>first;
        vector<int>second;
        for(auto &e : edges){
            if(vec[e[1]] == -1){
                vec[e[1]] = e[0];
            }else{
                first = {vec[e[1]],e[1]};
                second = e;
                e[1] = -1;
            }
        }
        for(int i = 0; i <= vec.size();++i) vec[i] = -1;
        for(auto &e : edges){
            if(e[1] == -1) continue;
            int root1 = findroot(e[0],vec);
            int root2 = findroot(e[1],vec);
            if(root1 == root2) return first.empty() ? e : first;
            vec[root1] = root2;
        }
        return second;
    }
    
    int findroot(int e,vector<int>&vec){
        return vec[e] == -1 ? e : findroot(vec[e],vec);
    }
};
