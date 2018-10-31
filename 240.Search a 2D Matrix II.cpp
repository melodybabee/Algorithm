题意：
找到二维数组中的目标元素。074的follow up,区别在于本题数组不能蛇形输出，分别是在各自的行和列上由小到大排列的。
思路：
1.通过观察发现，数组的左下和右上比较有特点，以右上为例，向下增大，向左减小。
2.因此如果目标值大于数组中的值，向下移动；如果目标值小于数组中的值，向左移动。
3.一旦找到了返回true,否则返回false.
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0 || matrix[0].size() == 0) return false;
        if(target < matrix[0][0] || target > matrix.back().back()) return false;
        int m = matrix[0].size()-1;
        int n = 0;
        while(true){
            if(m < 0 || n >= matrix.size()) break;
            else if(target > matrix[n][m]) ++n;
            else if(target < matrix[n][m]) --m;
            else return true;
        }
        return false;
    }
};