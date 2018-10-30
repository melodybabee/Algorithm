题意：
把数组中为0的行和列都置为0。
思路：
1.本题如果是T(mn)或者T(m+n)的复杂度就属于容易题，直接新建一个数组判断为0的在新数组中刷新即可。
但是本题要求constant的空间复杂度，即不能新建数组。问题在于如果把一个为0的数字的行与列替换，那么后面的循环不知道是原先的0还是后面新替换的0.
2.那么首先需要判断第一行与第一列的元素，如果有0，说明本行／本列都应该被替换，但是为了不影响后面的循环，用一个标志位记录下来最后再操作。
3.循环除了第一行和第一列的数字，如果为0，把其对应的第一行和第一列更改为0.
4.再次循环除了第一行和第一列的数字，如果对应的第一行／第一列为0，那么把当前位置赋值为0.
5.最后回到第一行和第一列，如果标志位为true,那么直接把该行／该列都置为0。
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        bool line = false;
        bool col = false;
        for(int i = 0; i < m ;++i){
            if(matrix[i][0]==0) line = true;
        } 
        for(int j = 0; j < n ;++j){
            if(matrix[0][j]==0) col = true;
        }
        for(int i = 1; i < m ;++i){
            for(int j = 1; j < n; ++j){
                if(matrix[i][j] == 0){
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for(int i = 1; i < m ;++i){
            for(int j = 1; j < n; ++j){
                if(matrix[i][0] == 0 || matrix[0][j] == 0){
                    matrix[i][j] = 0;
                }
            }
        }
        if(line){
            for(int i = 0; i< m; ++i) matrix[i][0] = 0;
        }
        if(col){
            for(int j = 0; j< n; ++j) matrix[0][j] = 0;
        }
    }
};