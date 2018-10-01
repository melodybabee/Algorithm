分析题意，可知4的倍数的时候先拿的人输。
class Solution {
public:
    bool canWinNim(int n) {
        if(n%4 == 0) return false;
        return true;
    }
};