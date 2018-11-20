题意：
求出数组中值为1的区域周长。
方法一：数学思路
思路：
1.周长是由四条边构成的，那么数字为1的元素的个数*4。还需要再减去两块都为1的邻接元素的个数，因为是两个元素，所以需要*2.
2.遍历整个矩阵，当碰到1的时候，计数器+1，判断这个元素的左和上是否仍然为1，如果是，重复元素的计数器+1.
因为记录左和上不会影响下面元素的循环，同时也不会重复计算。
3.最后4*计数器-2*重复元素即为所求的周长。
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int count = 0;
        int repeat = 0;
        for(int i = 0; i < grid.size();++i){
            for(int j = 0; j < grid[0].size(); ++j){
                if(grid[i][j] == 1){
                    ++count;
                    if(i > 0 && grid[i-1][j] == 1) ++repeat;
                    if(j > 0 && grid[i][j-1] == 1) ++repeat;
                }
            }
        }
        return 4*count - 2*repeat;
    }
};
方法二：遍历
思路：
1.通过观察图发现，以左边界为例，只有当左边界为0或者它的同行前面一个元素为0的时候，左边界才被记入周长。
依次遍历矩阵中的各个元素即可，如果是0跳过，对于是1的元素分别对各边进行判断，最后输出周长。
其他三条边也可以通过这个方法遍历得到。
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int ans = 0;
        for(int i = 0; i < grid.size();++i){
            for(int j = 0; j < grid[0].size();++j){
                if(grid[i][j] == 0) continue;
                if(i == 0 || grid[i-1][j] == 0) ++ans;
                if(j == 0 || grid[i][j-1] == 0) ++ans;
                if(i == grid.size()-1 || grid[i+1][j] == 0) ++ans;
                if(j == grid[0].size() -1 || grid[i][j+1] == 0)++ans;
            }
        }
        return ans;
    }
};
