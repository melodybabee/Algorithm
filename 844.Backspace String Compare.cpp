Backspace 退后一格
题意：包含退格键判断两个字符串是否相等
思路：
1.分别对两个字符串进行处理，如果遇到#且坐标大于等于2的时候，直接获取字符串前半部分和后半部分
注意截取之后字符串退回到两位之前
2.如果坐标小于2，那么直接获取后半部分即可，因为此时需要从头循环，因此坐标位置等于-1
3.最后判断两个字符串是否相等
注意：
s.substr()函数内的两个变量表示起始位置，和所获取的子串的长度
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        for(int i = 0; i < S.size(); ++i){
            if(S[i] == '#' && i -2 >= 0) {
                S = S.substr(0,i-1) + S.substr(i+1);
                i = i-2;
            }
            if (S[i] == '#' && i -2 < 0){
                S = S.substr(i+1);
                i = -1;
            } 
        }
        for(int i = 0; i < T.size(); ++i){
            if(T[i] == '#' && i -2 >= 0) {
                T = T.substr(0,i-1) + T.substr(i+1);
                i = i-2;
            }
            if (T[i] == '#' && i -2 < 0){
                T = T.substr(i+1);
                i = -1;
            } 
        }
        return S == T;
    }
};