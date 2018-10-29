题意：
N皇后问题
方法：DFS回溯递归
思路：
1.一层一层向下扫描，用一个p数组来思路每行中Q的位置
2.设置一个行参数，从第0行开始，在递归方法中循环列，注意判断每一行的每一列是否能放入皇后，如果能，放入，进行下一行的递归
如果判断到某一位发现冲突，回溯调用递归，把p中的所有位置置为-1，重新判断
一旦行数等于p的大小的时候，说明已经找到一个解，那么创建一个n行string类型的vector,默认置为'.',再把p中的元素对应放到每一行的每一位中
3.判断是否能放的方法是：
循环p数组，如果该列的值等于p数组中存在过的某个值或者行的绝对值等于列的绝对值，那么为false,否则为true
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<int> p(n,-1);
        FindQueen(p,0,ans);
        return ans;
    }
    void FindQueen(vector<int> &p, int row, vector<vector<string>>&ans){
        int n = p.size();
        if(row == n){
            vector<string> ret(n,string(n,'.'));
            for(int i = 0; i < n;++i){
                ret[i][p[i]] = 'Q';
            }
            ans.push_back(ret);
        }else{
            for(int col= 0; col< n; ++col){
                if(isQ(p,row,col)){
                    p[row] = col;
                    FindQueen(p,row+1,ans);
                    p[row] = -1;
                }
            }
        }
    }
    bool isQ(vector<int> &p, int row, int col){
        for(int i = 0; i< row;++i){
            if(col == p[i] || abs(row- i) == abs(col - p[i])){
                return false;
            }
        }
        return true;
    }
};