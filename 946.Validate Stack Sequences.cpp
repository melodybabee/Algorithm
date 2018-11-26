题意：
给出一个push数组一个pop数组，问能否通过push和pop把数组归零。
思路：
1.本题模拟的就是stack的过程，所以建立一个栈，从push数组中一个一个push数字
当栈顶元素等于pop数组中的当前元素时，栈顶元素出栈，pop数组指针后移
2.最后判断栈是否为空即可
注意：
1.在输出栈顶元素的时候需要判断栈是否为空，当不为空的时候可以pop。如果不判断会runtime error
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int>st;
        int index = 0;
        for(int i = 0; i < pushed.size(); ++i){
            st.push(pushed[i]);
            while(!st.empty() && st.top() == popped[index]){
                st.pop();
                ++index;
            }
        }
        return st.empty();
    }
};
方法二：