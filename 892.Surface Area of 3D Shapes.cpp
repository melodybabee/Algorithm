题意：
根据给出的数组求出3D图形的表面积。
思路：
1.3D图形的表面积等于其原有的总面积减去重复的部分。
2.那么循环二维数组，分别计算总数和重复的部分。最后的个数是总数*6-重复的部分*2.
3.每遍历到一个数字，按照它的个数进行计算，因为一个正方体有6个面，那么任何两个叠加在一起的正方体就会有重复的一面。重复的面数是总个数-1
4.还需要统计每一行和每一列中重复的面数，相邻位置重复的面数是与它前面或者上面正方体中的较小值。
5.最后计算表面积即可。表面积包括在外面的面积和底部一层的面积。
class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int total = 0;
        int common = 0;
        for(int i = 0; i < grid.size();++i){
            for(int j = 0; j < grid[0].size(); ++j){
                if(grid[i][j]){
                    total += grid[i][j];
                    common += grid[i][j]-1;
                    if(i > 0) common += min(grid[i-1][j],grid[i][j]);
                    if(j > 0) common += min(grid[i][j],grid[i][j-1]);
                }
            }
        }
        return total * 6 - 2 * common;
    }
};