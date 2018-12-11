题意：找到数组中的峰值。
思路：
1.对数组进行二叉搜索，因为题目中说明了是一定存在的，因此从中间开始查找，如果比下一位小，说明在上坡，移动左指针。
如果比下一位大，说明在下坡，移动右指针。
当左右指针重合的时候就是要找的值。
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        int left = 0;
        int right = A.size()-1;
        while(left < right){
            int mid = left +(right-left)/2;
            if(A[mid] < A[mid+1]){
                left = mid +1;
            }else if(A[mid] > A[mid+1]){
                right = mid;
            }
        }
        return right;
    }
};