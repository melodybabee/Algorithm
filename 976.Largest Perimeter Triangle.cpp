题意：找到数组中能形成的三角形的最大周长
方法一：暴力拆解
思路：
1.把数组排序，这样大的值就会在数组的尾部。
2.利用两边之和大于第三边来进行判断，只要满足条件，那么直接返回周长的值。
class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        sort(A.begin(),A.end());
        for(int i = A.size()-1;i >= 0; --i){
            for(int j = i-1; j >= 0; --j){
                for(int k = j-1; k >= 0; --k){
                    if(A[j] + A[k] > A[i]) {
                        return A[j] + A[i] +A[k];
                    }
                }
            }
        }
        return 0;
    }
};
方法2:暴力拆解优化
思路：
对于遍历到的每个数字，只需要判断其前一位和再前一位即可，因为如果当前不满足，把指针向前移动的话更不会满足。
class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        sort(A.begin(),A.end());
        for(int i = A.size()-1;i >= 2; --i){
            if(A[i] < A[i-1] + A[i-2]) return A[i] + A[i-1] + A[i-2];
        }
        return 0;
    }
};