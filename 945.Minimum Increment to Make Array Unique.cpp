题意：
找到最少次数的变换使数组无重复元素。
T(n) = O(nlogn);
思路：
1.看到去重第一反应会想到用hashmap,但是一个一个存储再查找的方法会TLE
2.看到题目中的数量级是0 <= A.length <= 40000，0 <= A[i] < 40000，可以根据给出的数量级来大值判断用到的方法
3.那么本题应该用到搜索的方法,首先sort()把数组进行排序，开始循环数组
4.如果后一位小于等于前一位，那么返回值加上两个值的差+1，再把当前位置更新为前一位+1
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        sort(A.begin(),A.end());
        int ret = 0;
        for(int i = 1; i < A.size(); ++i){
            if(A[i] <= A[i-1]){
                ret += A[i-1] - A[i]+1;
                A[i] = A[i-1]+1;
            }
        }
        return ret;
    }
};