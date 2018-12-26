题意：293 follow up,翻转正号判断是否能够赢得比赛
思路：
1.利用回溯法逐一进行判断，如果更改完一个字符串之后，对该字符串继续调用递归函数，判断是否可以更改，如果不能，那么直接返回true，证明可以赢;
回溯过后需要把已经更改过的字符再次复原，继续下一次操作；
如果到最后都没有返回true,那么说明不能赢，返回false
class Solution {
public:
    bool canWin(string s) {
        if(s.size() == 0) return false;
        for(int i= 0; i < s.size()-1; ++i){
            if(s[i] == '+' && s[i+1] == '+'){
                s[i] = '-';
                s[i+1] = '-';
                if(!canWin(s)) return true;
                s[i] = '+';
                s[i+1] = '+';
            }
        }
        return false;
    }
};