题意：猜价格问题
思路：
1.题目中给出了一个API来判断当前数字比目标数字大还是小
2.那么用二叉搜索进行查找，注意-1是my number is lower的意思，指当前数字高了，所以应该缩小右侧的范围
3.一旦找到返回为0的数字那么直接返回该数字。
// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        if (guess(n) == 0) return n;
        int left = 1;
        int right = n;
        while(left < right){
            int mid = left + (right - left)/2;
            int temp = guess(mid);
            if(temp == 0) return mid;
            if(temp == 1) left = mid;
            else right = mid;
        }
        return right;
    }
};