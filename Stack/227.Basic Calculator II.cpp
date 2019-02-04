truncate截短
题意：
给出四则运算的字符串，计算出结果。
方法一：stack
思路：
1.因为后进先出的规则，因此首先把数字放入栈中，注意因为会有两个数字相连的情况，因此需要一个值来记录下数字，并且做*10操作
2.第一位数字看作是做加法运算，用一个符号值记录下来。
3.如果遍历到的不是数字，或者到了数字的最后一位，判断其之前的符号是什么如果是+，入栈；如果是减，相反数入栈。
4.如果是乘法或者除法，那么用当前值和栈顶元素进行操作，再把结果入栈。
5.当循环完成之后依次相加栈中的元素，为最终结果。
注意：
1.把字符转换为数字的时候，数值的ASCII码要比字符的大，0是48，因此数字-'0'就是数值。
而如果标点符号-'0'会小于0，那么根据是否小于0判断是否是标点。
2.因为还有空格的存在，如果是空格，直接跳过，但是判断是否是标点的时候小于0后要满足同时不为空格。空格的ASCII码是20.
class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int num = 0;
        int ret = 0;
        char op = '+';
        for(int i = 0 ; i < s.size();++i){
            if(s[i] - '0'>= 0){
                num = 10*num + s[i]-'0';
            }
            if(s[i]- '0' < 0 && s[i] != ' ' || i == s.size()-1){
                if(op == '+') st.push(num);
                if(op == '-') st.push(-num);
                if(op == '*'|| op =='/'){
                    int temp = (op == '*')? st.top() * num : st.top()/num;
                    st.pop();
                    st.push(temp);
                }
                op = s[i];
                num = 0;
            }
        }
        while(!st.empty()) {
            ret += st.top();
            st.pop();
        }
        return ret;
    }
};

方法2:遍历
思路：
1.同样需要先记录下符号，如果是数字直接相加，如果是标点开始选择之前记录的符号，对之前的数字进行操作。
2.如果是加减或者到了最后一位，直接在结果中记录下该值，表明不需要有再次计算的机会，如果是乘除，那么会和后面的字符在此进行计算
3.只要遍历到符号，那么最后更新符号，同时更新num的值为0.
注意：
1.在switch和case写法中，每一种情况写完后直接break;
class Solution {
public:
    int calculate(string s) {
        char op = '+';
        int ret = 0;
        int num = 0;
        int curret = 0;
        for(int i = 0; i < s.size();++i){
            if(s[i] - '0' >= 0 && s[i] - '0' <=9){
                num = 10*num + s[i] - '0';
            }
            if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i]=='/' || i == s.size()-1){
                switch(op){
                    case '+': curret += num; break;
                    case '-': curret -= num; break;
                    case '*': curret *= num; break;
                    case '/': curret /= num; break;
                }
                if(s[i] == '+' || s[i] == '-' ||i == s.size()-1){
                    ret += curret;
                    curret = 0;
                }
                op = s[i];
                num = 0;
            }
        }
        return ret;
    }
};

2.3复习
方法一：stack
注意：
1.要首先首先记录下符号，再按照符号对数值进行操作！
2.因为有可能最后一位是数字，那么这种情况下不能用if...else...必须用if来判断，这样会在进入第一个loop之后再接着进入第二个loop
class Solution {
public:
    int calculate(string s) {
        int ret = 0;
        int num = 0;
        char op = '+';
        stack<int>st;
        for(int i = 0;i < s.size(); ++i){
            if(s[i]-'0' >= 0){
                num = 10*num + s[i] - '0';
            }
            if(s[i]-'0' < 0 && s[i] != ' ' || i == s.size()-1){
                if(op == '+') st.push(num);
                if(op == '-') st.push(-num);
                if(op == '*' || op == '/'){
                    int temp = (op == '*') ? st.top()*num: st.top()/num;
                    st.pop();
                    st.push(temp);
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
方法2:switch...break
注意：
需要用一个cur变量来记录下当前的值，如果是加减法或者到了最后一位，那么直接输出在结果中，如果是乘除法那么暂时保存。
符号仍然需要比数值提前一步进行判断
class Solution {
public:
    int calculate(string s) {
        int ret = 0;
        int num = 0;
        char op = '+';
        int cur = 0;
        for(int i = 0;i < s.size(); ++i){
            if(s[i]-'0' >= 0){
                num = 10*num + s[i] - '0';
            }
            if(s[i]-'0' < 0 && s[i] != ' ' || i == s.size()-1){
                switch(op){
                    case '+':cur += num; break;
                    case '-':cur -= num; break;
                    case '*':cur *= num; break;
                    case '/':cur /= num; break;
                }
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