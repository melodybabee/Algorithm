题意：最大栈
思路：
1.同样设置两个栈，一个为普通的栈，一个是最大栈。
2.注意pop()的时候也需要把最大栈中的元素pop出来，popMax()的时候也需要把普通栈中的元素pop出来
class MaxStack {
private:
    stack<int>st;
    stack<int>maxst;
public:
    /** initialize your data structure here. */
    MaxStack() {
        
    }
    
    void push(int x) {
        st.push(x);
        if(maxst.empty() || x >= maxst.top()) maxst.push(x);
    }
    
    int pop() {
        if(!maxst.empty() && maxst.top() == st.top()) maxst.pop();
        int temp = st.top();
        st.pop();
        return temp;
    }
    
    int top() {
        return st.top();
    }
    
    int peekMax() {
        return maxst.top();
    }
    
    int popMax() {
        int temp = maxst.top();
        stack<int> tempst;
        while(st.top() != maxst.top()){
            tempst.push(st.top());
            st.pop();
        }
        maxst.pop();
        st.pop();
        while(!tempst.empty()){
            push(tempst.top());
            tempst.pop();
        }
        return temp;
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack obj = new MaxStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.peekMax();
 * int param_5 = obj.popMax();
 */