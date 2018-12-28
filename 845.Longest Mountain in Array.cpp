题意：找到数组中最长的山的长度
思路：
方法一：遍历分别找山底和山顶
T(n) = O(n), S(n) = 1;
思路：
1.首先从1开始进行循环，分别寻找山底和山顶，山底表示当前的值都小于其左右的值
山顶表示其当前的值都大于其左右的值。
2.当山顶存在的时候更新结果值，需要判断当前值是否比前一位小，即在山坡向下的位置，如果不是，说明此山已经结束，那么山峰的状态置为-1，重新寻找山峰和山底进行更新
class Solution {
public:
    int longestMountain(vector<int>& A) {
        int ret = 0;
        int s = 0;
        int p = -1;
        for(int i = 1 ; i < A.size();++i){
            if(p != -1){
                if(A[i] < A[i-1]) ret = max(ret,i-s+1);
                else p = -1;
            }
            if(A[i] > A[i-1] && i < A.size()-1 && A[i] > A[i+1]){
                    p = i;
                }
            if(i < A.size()-1 && A[i] <= A[i-1] && A[i] < A[i+1]){
                s = i;
            }
        }
        return ret;
    }
};
方法2:用数组进行循环
T(n) = O(n)
思路：
1.分别设置一个上升数组和一个下降数组，从后向前循环如果是上升的，那么下降数组+1
从前向后循环如果是上升的，那么上升数组+1
最后一遍循环把两个数组相加，再加上山峰处的值+1。
注意：
从倒数第二位和第二位进行更新，最后需要加上山峰值。因为有+1的部分因此需要在数组都不为0的时候相加。
class Solution {
public:
    int longestMountain(vector<int>& A) {
        vector<int>up(A.size(),0);
        vector<int>down(A.size(),0);
        int res = 0;
        for(int i = A.size()-2; i >= 0; --i) if(A[i] > A[i+1])down[i] = down[i+1]+1;
        for(int i = 1; i < A.size(); ++i) if(A[i] > A[i-1])up[i] = up[i-1] +1;
        for(int i = 0; i < A.size(); ++i){
            if(up[i] && down[i])res = max(res, up[i] + down[i] + 1);
        }
        return res;
    }
};
方法3:方法2基础上的优化，不用额外的空间,思路类似方法1，比方法1写起来简洁
class Solution {
public:
    int longestMountain(vector<int>& A) {
        int res = 0;
        int up = 0;
        int down = 0;
        for(int i = 1; i < A.size();++i){
            if(down && A[i] > A[i-1] || A[i] == A[i-1]) up = down = 0;
            up += A[i] > A[i-1];
            down += A[i] < A[i-1];
            if(up && down)res = max(res,up+down + 1);
        }
        return res;
    }
};
