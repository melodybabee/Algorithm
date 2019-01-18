题意：
找出数组中离当前位置最近的，大于当前位置的坐标差。
思路：
1.类似找比自己大的，最近的位置利用栈能最快的解决问题
2.遍历数组，把坐标放入栈，如果需要更大的，更新结果数组，再入栈，维护一个单调递减的栈，遇到更大的就输出。
注意：
1.需要新建一个数组，在原数组基础上更新的问题是如果没有更大的不好判断，所以新的结果数组的初始值就是不满足条件时的情况。
2.注意stack判断完之后还及时弹出。
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        stack<int>st;
        vector<int> ans(T.size(),0);
        for(int i = 0; i < T.size(); ++i){
            while(!st.empty() && T[i] > T[st.top()]){
                ans[st.top()] = i-st.top();
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }
};