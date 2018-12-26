分析题意，可知4的倍数的时候先拿的人输。
class Solution {
public:
    bool canWinNim(int n) {
        if(n%4 == 0) return false;
        return true;
    }
};

12.25复习
因为可以拿1，2，3个。如果可以被4整除，只要第二个人和第一个人凑整拿4的倍数，第一个人就赢不了。
class Solution {
public:
    bool canWinNim(int n) {
        if(n % 4 == 0) return false;
        else return true;
    }
};