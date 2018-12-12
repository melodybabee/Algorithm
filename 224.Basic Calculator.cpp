题意：有加减括号的四则运算，227，772follow up
方法一：递归
思路：
1.遇到数字直接相加，遇到+，-那么判断之前的符号进行运算，更新到结果值中同时数字值为0
2.遇到括号进行递归操作。
class Solution {
public:
    int calculate(string s) {
        int ret = 0;
        int num = 0;
        char op = '+';
        for(int i = 0; i < s.size();++i){
            if(s[i] - '0' >= 0 && s[i] - '0' <=9){
                num = 10*num + s[i] - '0';
            }else if(s[i] == '('){
                int j = i;
                int count = 0;
                for(i; i < s.size(); ++i){
                    if(s[i] == '(') ++count;
                    if(s[i] == ')') --count;
                    if(count == 0) break;
                }
                num = calculate(s.substr(j+1,i-j+1));
            }
            
            if(s[i] == '+' || s[i] == '-' || i == s.size()-1){
                if(op == '+'){
                    ret += num;
                    num = 0;
                }
                if(op == '-'){
                    ret -= num;
                    num = 0;
                }
                op = s[i];
            }
        }
        return ret;
    }
};

方法2:stack
思路：
1.递归的思路是相同的，只不过用一个stack来存放每个符号前的结果，最后统一相加。
class Solution {
public:
    int calculate(string s) {
        int ret = 0;
        int num = 0;
        stack<int>st;
        char op = '+';
        for(int i = 0; i <s.size();++i){
            if(s[i] - '0' >=0){
                num  = 10*num +s[i]-'0';
            }
            else if (s[i] == '('){
                int j = i;
                int count = 0;
                for(i ; i < s.size();++i){
                    if(s[i] == '(') ++count;
                    if(s[i] == ')') --count;
                    if(count == 0)break;
                }
                num = calculate(s.substr(j+1, i-j+1));
            }
            if(s[i] - '0' < 0 && s[i] != ' ' || i == s.size()-1){
                if(op == '+') st.push(num);
                if(op == '-') st.push(-num);
                op = s[i];
                num = 0;
            }
        }
        while(!st.empty()){
            ret += st.top();
            st.pop();
        }
        return ret;
    }
};
方法3:普通遍历
思路：
1.注意在有数字的时候就把所有的数字都计算出来结果记录到结果值中。
2.用1和-1来标记是正数还是负数。
3.如果遇到了左括号把结果入栈，当前的正负号入栈，结果值为0，标点符号为1.恢复初始值。
遇到右括号出栈的时候先乘上符号在加上结果值。
栈是用来处理括号的。
class Solution {
public:
    int calculate(string s) {
        int ret = 0;
        int sign = 1;
        stack<int>st;
        for(int i = 0; i < s.size();++i){
            if(s[i] - '0' >= 0){
                int num = 0;
                while(s[i] -'0' >= 0 && i < s.size()){
                    num = 10*num +s[i] -'0';
                    ++i;
                }
                ret += sign*num;
                --i;
            }else if(s[i] == '+'){
                sign = 1;
            }else if(s[i] == '-'){
                sign = -1;
            }else if(s[i] == '('){
                st.push(ret);
                st.push(sign);
                ret = 0;
                sign =1;
            }else if(s[i] == ')'){
                ret *= st.top();
                st.pop();
                ret += st.top();
                st.pop();
            }
        }
        return ret;
    }
};