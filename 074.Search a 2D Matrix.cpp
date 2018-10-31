题意：
判断二维数组中有没有目标值。
方法一：先行遍历，再列遍历
思路：
1.因为二维数组是排序好的，因此首先判断目标数字在哪一行，注意如果不在范围内，一开始就直接返回false
那么所有数字都应该在范围内，那么比较每行第一个元素得知目标元素在哪一行
注意如果是在最后一行，会首先跳出循环，那么在循环外部需要重新定义一下
2.再在目标行的列数里面找有没有目标元素即可。
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size();
        int n = matrix[0].size();
        int row = 0;
        int i = 0;
        if(target > matrix[m-1][n-1] || target < matrix[0][0]) return false;
        for(i = 0; i < m ;++i){
            if(matrix[i][0] == target){
                row = i;
                break;
            }else if(matrix[i][0] > target){
                row = i-1;
                break;
            }else continue;
        }
        if(i == m && row == 0) row = m-1;
        
        for(int j = 0; j< n; ++j){
            if(matrix[row][j] == target) return true;
        }
        return false;
    }
};
方法二：二分法
思路：
分别对行和列进行二分判断即可。
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0 || matrix[0].size() == 0) return false;
        if(target < matrix[0][0] || target > matrix.back().back()) return false;
        int left = 0;
        int right = matrix.size()-1;
        while(left <= right){
            int mid = (left + right)/2;
            if (matrix[mid][0] == target) return true;
            else if(matrix[mid][0] < target) left = mid +1;
            else right = mid-1;
        }
        int line = right;
        left = 0;
        right = matrix[line].size()-1;
        while(left <= right){
            int mid = (left + right)/2;
            if(matrix[line][mid]  == target) return true;
            else if(matrix[line][mid] > target) right = mid -1;
            else left = mid +1;
        }
        return false;
    }
};