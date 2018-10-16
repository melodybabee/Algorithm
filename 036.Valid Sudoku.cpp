Sudoku 数独
题意：
找出这个数独矩阵是否是有效的，有效是指列，行和一个小的3*3矩阵中没有重复的数字
有效不等于有解
思路：
1.如果数独的行和列不等于9，那么直接返回false;
2.分别用两个for循环来循环行和列，设置一个bool类型的vector来记录是否有重复的值
vector默认为false,因为vector的index与数字1-9一一对应，放入之前先查找该位是否是ture,如果是true，表示有重复，如果是false,改变为true
这一点是简化版的hashtable思想
3.在循环3*3矩阵的时候，需要再初始化一下当前的行和列的位置进行判断。
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        if(board.size() != 9 || board[0].size() != 9) return false;
        
        for(int i = 0; i < 9; ++i){
            vector<bool>flag (9,false);
            for(int j = 0; j < 9; ++j){
                if(!isdigit(board[i][j])) continue;
                int ret = board[i][j] - '1';
                if(flag[ret] == true) return false;
                flag[ret] = true;
            }
        }
        for(int j = 0; j < 9; ++j){
            vector<bool>flag (9,false);
            for(int i = 0; i < 9; ++i){
                if(!isdigit(board[i][j])) continue;
                int ret = board[i][j] - '1';
                if(flag[ret] == true) return false;
                flag[ret] = true;
            }
        }
        for(int j = 0; j < 3; ++j){
            for(int i = 0; i < 3; ++i){
                int row = 3*i;
                int line = 3*j;
                vector<bool>flag (9,false);
                for(int p = row; p < row+3; ++p){
                    for(int q = line; q < line +3; ++q){
                        if(!isdigit(board[p][q])) continue;
                        int ret = board[p][q] - '1';
                        if(flag[ret] == true) return false;
                        flag[ret] = true;
                    }
                }
            }
        }
        return true;
    }
};
优化（时间复杂度不变）：
因为本题的本质是三次循环，只是循环的位数不同，所以可以简化for循环的过程，代码写法如下
class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        if (board.empty() || board[0].empty()) return false;
        int m = board.size(), n = board[0].size();
        vector<vector<bool> > rowFlag(m, vector<bool>(n, false));
        vector<vector<bool> > colFlag(m, vector<bool>(n, false));
        vector<vector<bool> > cellFlag(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] >= '1' && board[i][j] <= '9') {
                    int c = board[i][j] - '1';//因为vector的位数从0开始，所以需要把当前的数字-1
                    if (rowFlag[i][c] || colFlag[c][j] || cellFlag[3 * (i / 3) + j / 3][c]) return false;
                    rowFlag[i][c] = true;
                    colFlag[c][j] = true;
                    cellFlag[3 * (i / 3) + j / 3][c] = true;
                }
            }
        }
        return true;
    }
};