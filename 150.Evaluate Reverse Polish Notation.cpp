题意：计算逆波兰表达式
思路：
1.波兰表达式的意思是把操作数放前面，把操作符后置的一种写法
2.那么为了计算出这样数值的结果，用stack后进先出的性质能够很好的解决
因为给出的数组一定是有效的排列，因此只要是符号，那么获取栈顶的两个元素，计算后再入栈
3.最后的结果返回栈顶元素即可
注意：
1.注意数值类型的统一
string to int:stoi()
int to string: to_string()
2.注意为了避免除以0，应该计算的时候用后出栈的数字计算先出栈的数字
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<string>st;
        for(int i = 0; i < tokens.size(); ++i){
            if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/"){
                int q = stoi(st.top());
                st.pop();
                int p = stoi(st.top());
                st.pop();
                if(tokens[i] == "+") tokens[i] = to_string(p + q);
                if(tokens[i] == "-") tokens[i] = to_string(p - q);
                if(tokens[i] == "*") tokens[i] = to_string(p * q);
                if(tokens[i] == "/") tokens[i] = to_string(p / q);
            }
            st.push(tokens[i]);
        }
        return stoi(st.top());
    }
};