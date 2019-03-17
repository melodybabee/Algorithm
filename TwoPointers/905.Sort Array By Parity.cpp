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

3.16复习
1.双指针两端开始找，左侧找奇数右侧找偶数进行交换，注意需要一直保持左指针小于右指针
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int left = 0;
        int right = A.size()-1;
        while(left < right){
            while(A[left] % 2 == 0 && left < right) ++left;
            while(A[right] % 2 != 0 && left < right) --right;
            swap(A[left],A[right]);
        }
        return A;
    }
};

优化：i，j同时指向头部位置，j负责找到偶数的位置，只要找到了就与i交换，i向后移动
所以如果最开始就一直是偶数的话那么一直在自己与自己交换
这样j领先i的位置就是奇数，i前面的位置到数组的最开始都是偶数，当j到达数组尾部的时候结束循环
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        for(int i = 0, j = 0; j < A.size(); ++j){
            if(A[j] % 2 == 0) swap(A[i++],A[j]);
        }
        return A;
    }
};
