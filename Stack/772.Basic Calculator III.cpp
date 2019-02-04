题意：
对string进行四则运算，有括号。227 follow up.
思路：
1.没有括号的部分和227相同。如果遇到括号那么直接进入递归流程。
2.当遇到左括号的时候开始，设置一个j位记录下这个位置，然后开始前进i,如果i是左括号，那么计数器+1，如果是右括号那么减1
当计数器为0的时候break.注意i是从它停在的位置开始计算的，因此计数器需要从0开始计算,先左后右。
3.对于括号内的子串调用递归，注意因为j记录的是最开始的位置，所以子串的开头部分是j+1,长度就是i-j+1
用num记录下递归的结果。i已经在递归结束的位置上。
class Solution {
public:
    int calculate(string s) {
        char op = '+';
        int ret = 0;
        int num = 0;
        int curret = 0;
        for(int i = 0; i < s.size(); ++i){
            char c = s[i];
            if(c -'0' >= 0 && c -'0' <= 9){
                num = 10*num + c-'0';
            }else if(c == '('){
                int j = i;
                int count = 0;
                for(i ; i < s.size(); ++i){
                    if(s[i] == '(') ++count;
                    if(s[i] == ')') --count;
                    if(count == 0) break;
                }
                num = calculate(s.substr(j+1,i-j+1));
            }
            if(c == '+' || c == '-' || c == '*' || c == '/' || i == s.size()-1){
                switch(op){
                    case '+':curret += num;break;
                    case '-':curret -= num;break;
                    case '*':curret *= num;break;
                    case '/':curret /= num;break;    
                }
                if(c == '+' || c == '-' || i == s.size()-1){
                    ret += curret;
                    curret = 0;
                }
                op = c;
                num = 0;
            }
        }
        return ret;
    }
};

2.3复习：
注意：
1.可以不用switch...case...break来判断，但是要注意写清楚if...else
2.在进入递归的时候要从当前停下的位置(j)的下一位开始进入递归
class Solution {
public:
    int calculate(string s) {
        int ret = 0;
        int num = 0;
        int cur = 0;
        char op = '+';
        for(int i = 0; i < s.size(); ++i){
            if(s[i] -'0' >= 0){
                num = 10*num + s[i] -'0';
            }
            if(s[i] == '('){
                int count = 0;
                int j = i;
                for(i; i< s.size();++i){
                    if(s[i] == '(') ++count;
                    if(s[i] == ')') --count;
                    if(count == 0)break;
                }
                num = calculate(s.substr(j+1,i-j+1));
            }
            if((s[i] - '0' < 0 && s[i] != ' ')|| i == s.size()-1){
                if(op == '+') cur += num;
                else if(op == '-') cur -= num;
                else if(op == '*') cur *= num;
                else if(op == '/') cur /= num;
                
                if(s[i] == '+' || s[i] == '-' || i == s.size()-1){
                    ret += cur;
                    cur = 0;
                }
                op = s[i];
                num = 0;
            }
        }
        return ret;
    }
};