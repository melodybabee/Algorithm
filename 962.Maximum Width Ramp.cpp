题意：找到数组中最远的大于等于某一个数字值的距离。
方法一：two pointers
O（n^2）的优化
思路：
1.循环数组，每循环到一个新的位置从右侧开始依次向左侧移动，找到第一个大于等于左侧值的位置，记录下两者之间的长度。
2.逐渐把左指针向右移动，更新长度，最后返回最长的结果。
注意：
1.while循环需要循环到右指针大于左指针的时候，一旦相等直接跳出循环。
class Solution {
public:
    int maxWidthRamp(vector<int>& A) {
        int ret = 0;
        for(int i = 0; i < A.size(); ++i){
            int right = A.size()-1;
            if(right-i <= ret) break;
            while(right > i && A[right] < A[i]){
                --right;
            }
            ret = max(ret,right-i);
        }
        return ret;
    }
};

方法2:stack,利用单调栈
T(n) = O(nlogn);
思路：
1.首先从左到右循环，只要后面的元素小于栈顶元素，那么入栈，维持一个单调递减的栈
注意入栈的是每个元素的坐标位置，而不是元素的值
2.再由后向前开始循环，只要当前元素大于等于栈顶元素就把栈顶元素出栈，计算两者之间的距离，不断更新。
3.注意要先计算距离再pop出来，不然top()会取到新的值。
class Solution {
public:
    int maxWidthRamp(vector<int>& A) {
        stack<int>st;
        int ret = 0;
        for(int i = 0; i < A.size(); ++i){
            if(st.empty() || A[i] < A[st.top()]){
                st.push(i);
            }
        }
        for(int i = A.size()-1; i >= 0; --i){
            while(!st.empty() && A[i] >= A[st.top()]){
                ret = max(ret,i-st.top());
                st.pop();
            }
        }
        return ret;
    }
};