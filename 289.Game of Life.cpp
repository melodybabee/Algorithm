题意：康威生命游戏更新数组
方法一：暴力循环
思路：
1.题目中对于数组中的每个数字的游戏规则是：
如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡
如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活
如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡
如果死细胞周围正好有三个活细胞，则该位置死细胞复活
建立一个新数组，那么每遍历到一个数字，就去判断它周围的8的个位置上的1的个数，分情况进行更新即可。
2.最后用原数组等于新数组返回结果。
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        vector<vector<int>>ret (board.size(),vector<int>(board[0].size(),0));
        for(int i = 0; i < board.size();++i){
            for(int j = 0; j < board[0].size(); ++j){
                if(board[i][j] == 0){
                    if(count(board,i,j) == 3) ret[i][j] =1;
                    else ret[i][j] = 0;
                }else if(board[i][j] == 1){
                    if(count(board,i,j) < 2 ||count(board,i,j) > 3) ret[i][j] = 0;
                    else if (count(board,i,j) ==2 || count(board,i,j) == 3) ret[i][j] = 1;
                }
            }
        }
        board = ret;
    }
    
    int count(vector<vector<int>>& board, int i, int j){
        int ans = 0;
        int m = board.size();
        int n = board[0].size();
        if(i-1 >= 0 && board[i-1][j] == 1) ++ans;
        if(i+1 < m && board[i+1][j] == 1)++ans;
        if(j-1 >= 0 && board[i][j-1] == 1)++ans;
        if(j+1 < n && board[i][j+1] == 1)++ans;
        if(i-1 >= 0 && j-1 >= 0 && board[i-1][j-1] == 1)++ans;
        if(i+1 < m && j +1 < n && board[i+1][j+1] == 1)++ans;
        if(i-1 >= 0 && j +1 < n && board[i-1][j+1] == 1)++ans;
        if(i+1 < m && j-1 >= 0 && board[i+1][j-1] == 1)++ans;
        return ans;
    }
};
方法2:in-place方法,状态机转换
S(n) = O(1);
思路：
1.对原来的状态设置4个状态：
0： 死细胞转为死细胞
1： 活细胞转为活细胞
2： 活细胞转为死细胞
3： 死细胞转为活细胞
那么这个状态的既记录了初始状态也记录了结束状态，那么遍历到每个位置都可以根据当前的状态进行统计。
在最后的结果中对数组中的所有数字进行2取余，能得到最后的结果。
2.注意遍历上下左右8个方向的时候可以提前设置一个数组，每次分别更新横纵坐标即可。
C++中的数组声明，要有[],根据数组中的类型声明为int
int dx[] = {-1,-1,-1,0,0,1,1,1};
int dy[] = {-1,0,1,-1,1,-1,0,1};
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        int dx[] = {-1,-1,-1,0,0,1,1,1};
        int dy[] = {-1,0,1,-1,1,-1,0,1};
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n ; ++j){
                int count = 0;
                for(int k = 0; k < 8; ++k){
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if(x >= 0 && y >= 0 && x < m && y < n && (board[x][y] == 1 || board[x][y] == 2)) ++count;
                }
                if(board[i][j] == 1 && (count < 2 || count > 3)) board[i][j] = 2;
                else if(board[i][j] == 0 && count == 3)board[i][j] = 3;
            }
        }
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n ; ++j){
                board[i][j] %= 2;
            }
        }
    }
};
