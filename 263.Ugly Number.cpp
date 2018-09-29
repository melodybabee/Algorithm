思路：
1.判断是否是ugly number,如果数字中仅包含2.3.5作为因子，就是ugly number.
2.分别对原数依次判断，是否是2，3，5的倍数，如果是，整除，判断最后与1是否相等
注意：
1.0的情况需要单独考虑
class Solution {
public:
    bool isUgly(int num) {
        if(num == 0) return false;
        while(num%5 == 0) num /= 5;
        while(num%3 == 0) num /= 3;
        while(num%2 == 0) num /= 2;
        return num==1;
    }
};