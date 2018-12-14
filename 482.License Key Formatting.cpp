题意：在字符串中穿插进入字符。
思路：
1.首先去掉原有的字符并把字母都转换为大写
2.从后往前循环开始插入'-'
注意：
1.转换为大写的方法是toupper(),注意从后往前时要大于0
class Solution {
public:
    string licenseKeyFormatting(string S, int K) {
        string str = "";
        for(int i = 0;i < S.size(); ++i){
            if(S[i] == '-') continue;
            if(isalnum(S[i])) str += toupper(S[i]);
        }
        
        for(int i = str.size()-K;i > 0; i-= K){
            str.insert(i,"-");
        }
        return str;
    }
};