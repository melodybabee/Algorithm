class MinStack {
public:
    stack<int> s1;
    stack<int> s2;
    void push(int x) {
	    s1.push(x);
	    if (s2.empty() || x <= getMin())  s2.push(x);	    
    }
    void pop() {
	    if (s1.top() == getMin())  s2.pop();
	    s1.pop();
    }
    int top() {
	    return s1.top();
    }
    int getMin() {
	    return s2.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */

 /*
 思路：
 1.不太明白题意，好像是找到stack中最小的值
 2.建两个stack, 一个按照push的顺序放入所有元素，一个如果为空，放入，后面只放比当前元素小的元素
 3.getMin()方法返回s2中的顶部元素，即当前数值的最小值
 4.调用pop()方法，如果s1的顶部元素与s2相同，即都是现在的最小值，s1s2同时pop顶部元素，如果不等，只pop s1,从而可以找到次小值
 5.top方法为执行s1的顶部元素

 问题：
 1.不明白为什么答案里面声明stack都要先声明private
 2.不明白test cases给出输入值的格式，找不到main函数
 3.不明白原题目中MinStack(){}的含义，及本题的数据结构
 */

12.10复习
注意：
1.最小栈是独立于原栈的新建的栈，只有一个栈无法实现本题的需要
2.注意如果普通栈返回的元素等于最小栈顶部元素，那么最小栈也要同样删除
class MinStack {
private:
    stack<int>st;
    stack<int>minst;
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        st.push(x);
        if(minst.empty() || x <= minst.top()){
            minst.push(x);
        }
        
    }
    
    void pop() {
        if(minst.top()== st.top()) minst.pop();
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minst.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */

3.26复习：
注意：
1.用一个栈用来维护比它的栈顶小的值，push的时候如果比栈顶元素小，那么push
pop的时候如果等于最小栈的栈顶元素，那么同时pop
2.题目中的pop方法与stack本身自带的pop方法不同，min.pop()弹出的还是min栈的顶部元素
class MinStack {
private:
    stack<int>st;
    stack<int>min;
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        st.push(x);
        if(min.empty() || x <= min.top()) min.push(x);
    }
    
    void pop() {
        if(st.top() == min.top()) min.pop();
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return min.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */