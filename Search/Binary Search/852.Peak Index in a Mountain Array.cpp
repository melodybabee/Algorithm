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

3.16复习
T(n) = O(n)
注意：因为题目中保证了一定会出现峰值，因此直接找到这个值即可
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        int i = 1;
        for(; i < A.size(); ++i){
            if(A[i] < A[i-1]) break;
        }
        return i-1;
    }
};

方法2:二叉搜索
注意：
1.二叉搜索的判断条件是判断中点处在上升还是下降的趋势上，那么如果在上升的趋势上，移动左边界，为了避免越界需要A[mid] < A[mid+1]比较
如果需要移动右边界那么中点和它前一位进行比较
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        int l = 0; 
        int r = A.size()-1;
        while(l < r){
            int mid = l + (r-l)/2;
            if(A[mid] < A[mid-1]) r = mid;
            else if(A[mid] < A[mid+1]) l = mid;
            else return mid;
        }
        return l;
    }
};