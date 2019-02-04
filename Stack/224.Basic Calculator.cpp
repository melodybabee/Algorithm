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

2.3复习
方法一：遍历
注意：
1.首先需要考虑两个数字字符相连的情况，需要转换为数字形式，用一个变量暂存下来，每次遇到都是之前的值*10加上新的值
2.如果遇到左边的括号，开始遍历找右侧的括号，左右相等的时候跳出，进行递归。
要用一个j指针记录下来左侧括号的位置，注意进入递归的时候要从j+1开始。
3.如果遇到了+,-那么在结果中用+或者-当前的值，临时的求和值归0.
****需要单独处理最后一位的情况，因为后面不会再次进入循环。因此符号要比当前遍历到的位置提前一位，起始默认为+。
每次做加法或者减法的是否都需要用当前的数值与之前的符号做运算。
4.判断最后一位的情况要放在最后，括号的判断要放在前面，因为如果括号在最后一位上，会直接跳出循环不能得到正确结果。
class Solution {
public:
    int calculate(string s) {
        int num = 0;
        int ret = 0;
        char op = '+';
        for(int i = 0; i < s.size();++i){
            if(s[i] -'0' <= 9 && s[i] - '0' >= 0){
                num = 10*num + s[i]-'0';
            }
            if(s[i] == '('){
                int j = i;
                int count = 0;
                for(i ; i < s.size();++i){
                    if(s[i] == '(') ++count;
                    if(s[i] == ')') --count;
                    if(count == 0)break;
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

方法2:栈
注意栈的遍历过程中要判断空格的情况，因为上面遍历如果是空格的话那么不存在这种情况会直接跳过。
正负号的ASCII码值小于0的ASCII码值。
class Solution {
public:
    int calculate(string s) {
        int num = 0;
        int ret = 0;
        char op = '+';
        stack<int>st;
        for(int i = 0; i < s.size();++i){
            if(s[i] -'0' <= 9 && s[i] - '0' >= 0){
                num = 10*num + s[i]-'0';
            }
            if(s[i] == '('){
                int j = i;
                int count = 0;
                for(i ; i < s.size();++i){
                    if(s[i] == '(') ++count;
                    if(s[i] == ')') --count;
                    if(count == 0)break;
                }
                num = calculate(s.substr(j+1,i-j+1));
            }
            
            if(s[i] - '0' < 0 && s[i] != ' ' || i == s.size()-1){
                if(op == '+'){
                    st.push(num);
                }
                if(op == '-'){
                    st.push(-num);
                }
                num = 0;
                op = s[i];
            }
        }
        while(!st.empty()){
            ret += st.top();

            st.pop();
        }
        return ret;
    }
};

方法3:用栈的普通遍历
注意：
思路是如果是数字就一直进行计算，正号为+1，负号为-1，也需要先初始化符号
遇到左括号把结果入栈，同时入栈符号。遇到右括号出符号出栈进行计算，满足了栈后进先出的性质
class Solution {
public:
    int calculate(string s) {
        int ret = 0;
        int op = 1;
        stack<int>st;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] -'0' >= 0){
               int num = 0;
                while(s[i] -'0' >= 0 && i < s.size()){
                     num = num*10 + s[i]-'0';
                     ++i;
                }
                ret += op*num;
                --i;
            }
            else if(s[i] == '+'){
                op = 1;
            }
            else if(s[i] == '-'){
                op = -1;
            }
            else if(s[i] == '('){
                st.push(ret);
                st.push(op);
                ret = 0;
                op = 1;
            }
            else if(s[i] == ')'){
                ret *= st.top();
                st.pop();
                ret += st.top();
                st.pop();
            }
        }
        return ret;
    }
};
