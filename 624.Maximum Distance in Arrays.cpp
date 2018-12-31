题意：找到数组中不同行上的最大距离
思路：
1.因为数组的每行是已经排序好的，所以直接找每一行的头部元素和尾部元素即可
2.那么把初始值设置为第一行的头部元素和尾部元素，从第二行开始进入循环，不断更新，使左更小，使右更大
3.用结果值记录当前行与之前最大值和最小值之间的结果差，找到最大的一个
注意：
1.本题不能计算同一行上的值，解决方案是用当前行与之前的结果交叉计算取最大。返回结果值。
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int left = arrays[0][0];
        int right = arrays[0].back();
        int ret = 0;
        for(int i = 1; i < arrays.size();++i){
            ret = max(ret,max(abs(left-arrays[i].back()),abs(right-arrays[i][0])));
            left= min(left,arrays[i][0]);
            right= max(right,arrays[i].back());
        }
        return ret;
    }
};