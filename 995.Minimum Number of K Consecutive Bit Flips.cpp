题意：给定规定的字符串长度，每次0，1对调，求出多少次能够把字符串全部更改为1
方法一：暴力求解,greedy
思路：
1.从字符串的头部开始循环，如果遇到0的，开始对其后面长度为K的字符串进行0，1替换，如果中途超出了字符串的范围，那么返回-1
2.如果在替换的过程中超过字符串的范围了，那么直接返回-1
3.最后如果成功返回计数器的值
class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        int count = 0;
        for(int i = 0; i < A.size(); ++i){
            if(A[i] == 0){
                ++count;
                for(int j = i ; j < i+K; ++j){
                    if(j >= A.size()) return -1;
                    A[j] = A[j] == 0 ? 1 : 0;
                }
            }
        }
        return count;
    }
};

O(n)方法待学习