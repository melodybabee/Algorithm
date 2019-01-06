题意：
煎饼排序，不断翻转数组使数组完成排序
思路：
1.首先从后往前循环数组，找到当前数组中的最大的数字，如果该数字不是在当前数组范围内的最后一位，那么对数组进行头部到最大位上数字的反转
2.翻转过后最大的数字会在头部，那么再对整个数组进行翻转。指针向前移动。
3.最后到第一位的时候已经是排序好的，直接返回即可。
注意：
1.reverse()函数的系数第一位表示起点位置，第二位表示需要翻转的长度，因此真正反转的部分的长度应该比坐标值大1
class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        vector<int>vec;
        for(int i = A.size(); i > 1; --i){
            int max = findmax(A,i);
            if(max != i-1){
                vec.push_back(max+1);
                reverse(A.begin(),A.begin()+max+1);
                vec.push_back(i);
                reverse(A.begin(), A.begin()+i);
            }
        }
        return vec;
    }
    int findmax(vector<int> &A, int i){
        int index = 0;
        for(int p = 0; p < i; ++p){
            if(A[p] > A[index]) {
                index = p;
            }
        }
        return index;
    }
};