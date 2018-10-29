题意：
N皇后问题找到解有几种。051简化。
思路：
1.同051题，用一个数组记录每行中应该放Q的列数，递归回溯。
如果行数等于p的大小，计数器+1
2.【注意】判断是否可以放入的时候，需要判断p中的每一个元素是否等于指定的列，等于就是false
或者对角线的值是否相等，行1-行2的绝对值=列1-列2的绝对值就是对角线相等
class Solution {
public:
    int totalNQueens(int n) {
        int ret = 0;
        vector<int>p(n,-1);
        findQueen(p,0,ret);
        return ret;
    }
    void findQueen(vector<int>&p, int row, int &ret){
        int n = p.size();
        if(row == n){
            ++ret;
        }else{
            for(int col = 0;col < n;++col){
                if(isvalid(p,row,col)){
                    p[row] = col;
                    findQueen(p,row+1,ret);
                    p[row] = -1;
                }
            }
        }
    }
    bool isvalid(vector<int>&p,int row, int col){
        for(int i = 0; i< row; ++i){
            if(p[i] == col || abs(row - i) == abs(col - p[i]))
                return false;
        }
        return true;
    }
};