题意：
307 follow up,在一个可改变数值大小的二维数组中求出指定坐标内的和。
思路：
1.跟一维数组构造binary Indexed tree一样，在一个可变的二维数组中求出指定位置的和，创建一个二维新数组记录已有值，一个二维树状数组便于求和。
二维树状数组中每一行和每一列都分别是一个树状数组按照其性质记录数组的和。
注意：
1.因为便于新的二维数组和树状数组计算求和，第0位都为空，从第1位开始计算，创建、更新和求和的时候要注意下标的变化。
class NumMatrix {
private:
    vector<vector<int>> matrixs;
    vector<vector<int>> bit;
public:
    NumMatrix(vector<vector<int>> matrix) {
        if(matrix.empty() || matrix[0].empty()) return;
        matrixs.resize(matrix.size()+1,vector<int>(matrix[0].size()+1,0));
        bit.resize(matrix.size()+1,vector<int>(matrix[0].size()+1,0));
        for(int i = 0 ; i < matrix.size();++i){
            for(int j = 0; j < matrix[0].size();++j){
                update(i,j,matrix[i][j]);
            }
        }
    }
    
    void update(int row, int col, int val) {
        int diff = val - matrixs[row+1][col+1];
        for(int i = row+1; i < matrixs.size(); i+=(i&-i)){
            for(int j = col +1; j < matrixs[0].size(); j += (j&-j)){
                bit[i][j] += diff;
            }
        }
        matrixs[row+1][col+1] = val;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return getSum(row2+1,col2+1)-getSum(row2+1,col1)-getSum(row1,col2+1)+getSum(row1,col1);
    }
    
    int getSum(int row, int col){
        int res = 0;
        for(int i = row; i > 0; i -=(i&-i)){
            for(int j = col; j > 0; j -=(j&-j)){
                res += bit[i][j];
            }
        }
        return res;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */