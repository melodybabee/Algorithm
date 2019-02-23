题意：把数组中的偶数前移，奇数后移
方法一：
T(n) = O(n), S(n) = O(n);
思路：
1.定义两个指针，能整除的放前面，不能整除的放后面，一个一个遍历即可
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        vector<int>ret(A.size());
        int j = 0;
        int end = A.size()-1;
        for(int i = 0; i < A.size(); ++i){
            if(A[i] % 2 == 0){
                ret[j] = A[i];
                ++j;
            }else{
                ret[end] = A[i];
                --end;
            }
        }
        return ret;
    }
};
方法2:
T(n) = O(n), S(n) = O(1);
思路：
1.判断两个数字的值，i用来记录奇数，j遇到偶数就和i进行交换，交换后i向后移动
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        for(int i = 0, j = 0; j < A.size(); ++j){
            if(A[j] % 2 == 0) swap(A[i++],A[j]);
        }
        return A;
    }
};