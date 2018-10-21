题意：
在只有0和1的字符串中，调整最少元素，使其成为递增的。
方法一：两轮循环
思路：
1.首先从头到尾循环，找到0的个数，意思是把0全部变成1需要几次。
2.再循环一次，如果遇到0，上述结果-1，意思是在这一步本身为0也是递增因此不用翻转，如果是1，那么需要翻转为0，所以+1
3.在整个循环的过程中不断取最小，最后返回最小
class Solution {
public:
    int minFlipsMonoIncr(string S) {
        int toone = 0;
        for(int i = 0; i < S.size(); ++i){
            if(S[i] == '0') ++toone;
        }
        int tozero = toone;
        for(int i = 0; i < S.size();++i){
            if(S[i] == '1') ++tozero;
            else{ --tozero;}
            toone = min(tozero,toone);
            
        }
        return toone;
    }
};
方法二：DP方法待学习。
总结：
1.比赛中没有AC这道题，第一遍循环过了，第二遍的思路是两个指针头尾循环，头遇到1，count+1，尾遇到0，count-1
但是这种情况下01110的结果是不对的，思路还是没有想清楚。
本题巧妙运用了二次循环的思路，并在过程中不断取小，值得复习。