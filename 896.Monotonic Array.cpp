monotone 单调的
题意：判断一个数组是否是单调的
思路：
1.先判断首尾元素，根据首尾元素的大小来比较数组中其他位置的大小顺序
class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        if(A.size() == 1) return true;
        int i = 0;
        int j = A.size()-1;
        if(A[i] == A[j]){
            for(int i = 1; i < A.size();++i){
                if(A[i] != A[i-1]) return false;
            }
        }
        else if(A[j] > A[i]){
            for(int i = 1; i < A.size();++i){
                if(A[i] < A[i-1]) return false;
            }
        }
        else if(A[j] < A[i]){
            for(int i = 1; i < A.size();++i){
                if(A[i] > A[i-1]) return false;
            }
        }
        return true;
    }
};