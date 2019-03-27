[把思路理清了，写代码是一件简单的事情!!]
设计思路：
1.如果string为空，返回true
2.循环string,一旦遇到左边界的符号，push到栈中
3.遇到右边界的符号，如果栈为空，false,取出栈顶元素，判断是否与右边界符号匹配
4.匹配的话去除栈顶元素，pop,否则返回false
5.如果最后栈为空，返回true，否则返回false


注意：
1.要考虑栈中是否为空，有可能是单边的情况
2.栈的操作
建栈：stack<char> st;
取栈顶元素：st.top()；
删除栈顶元素：st.pop();
入栈：st.push(入栈元素)；
判断栈是否为空：st.empty()；

class Solution {
public:
    bool isValid(string s) {
        if(s == " ") return true;
        stack<char> st;
        for (int i = 0; i < s.size(); ++i){
            if(s[i]=='(' || s[i]=='{' || s[i]=='[' ){
                st.push(s[i]);
            }
            else{
                if(st.empty()) return false;
                char comp = st.top();
                if(comp == '('&& s[i] == ')' ||comp == '{'&& s[i] == '}' ||comp == '['&& s[i] == ']')
                    st.pop();
                else{
                    return false;
                }
            }
        }
        if(st.empty()) 
            return true;
        else
            return false;
    }
};

二刷：
注意：
1.考虑单边的情况，报错出现了一个右单边，应该想到如果只出现左单边会怎么样
2.之前易错点再刷仍然易错，复习的时候着重看这些部分
class Solution {
public:
    bool isValid(string s) {
        if(s.empty()) return true;
        stack<char>st;
        for(int i = 0 ; i < s.size(); ++i){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
                st.push(s[i]);
            }
            else{
                if(st.empty()) return false;
                else{
                    char temp = st.top();
                    st.pop();
                    if(temp == '(' && s[i] == ')') continue;
                    if(temp == '{' && s[i] == '}') continue;
                    if(temp == '[' && s[i] == ']') continue;
                    else return false;
                }
            }
        }
        if(st.empty()) return true;
        else return false;
        
    }
};

3.27复习
注意：
1.if...else条件写清楚即可
class Solution {
public:
    bool isValid(string s) {
        stack<char>st;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == '[' || s[i] == '(' || s[i] == '{'){
                st.push(s[i]);
            }
            else{
                if(st.empty()) return false;
                else{
                    char temp = st.top();
                    st.pop();
                    if((temp == '(' && s[i] == ')') || (temp == '{' && s[i] == '}') || (temp == '[' && s[i] == ']')){
                        continue;
                    }else return false;
                }
            }
        }
        return st.empty();
    }
};
