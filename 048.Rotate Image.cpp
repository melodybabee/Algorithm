题意：
给一个矩阵，把这个矩阵顺时针旋转90度返回一个新矩阵。
思路1:先对角线反转，再上下反转
1.以从对角线为轴翻转，然后再以x轴中线上下翻转即可得到结果
1  2  3　　　 　　 9  6  3　　　　　  7  4  1
4  5  6　　-->　　 8  5  2　　 -->   8  5  2　　
7  8  9 　　　 　　7  4  1　　　　　  9  6  3
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0; i < n-1; ++i){
            for(int j = 0; j < n-i; ++j){
                swap(matrix[i][j],matrix[n-1-j][n-1-i]);
            }
        }
        for(int i = 0; i< n/2; ++i){
            for(int j = 0; j < n; ++j){
                swap(matrix[i][j],matrix[n-i-1][j]);
            }
        }
    }
};
思路二：先对矩阵取转置矩阵，再逐行反转
1  2  3　　　 　　 1  4  7　　　　　  7  4  1
4  5  6　　-->　　 2  5  8　　 -->   8  5  2　　
7  8  9 　　　 　　3  6  9　　　　    9  6  3
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                swap(matrix[i][j],matrix[j][i]);
            }
            reverse(matrix[i].begin(),matrix[i].end());
        }
    }
};
思路三：针对每一位进行一个周期的反转，一个周期为4个元素，顺时针旋转一次。
1  2  3               7  2  1            7  4  1
4  5  6      -->      4  5  6　　 -->  　 8  5  2　　
7  8  9               9  8  3　　　　　    9  6  3
注意坐标的位置。
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0; i< n/2; ++i){
            for (int j = i; j < n-i-1; ++j){
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-i-1][n-1-j];
                matrix[n-i-1][n-1-j] = matrix[j][n-1-i];    
                matrix[j][n-1-i] = temp;
            }
        }
    }
};
