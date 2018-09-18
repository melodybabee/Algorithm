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
 1.不太明白提议，好像是找到stack中最小的值
 2.建两个stack, 一个按照push的顺序放入所有元素，一个如果为空，放入，后面只放比当前元素小的元素
 3.getMin()方法返回s2中的顶部元素，即当前数值的最小值
 4.调用pop()方法，如果s1的顶部元素与s2相同，即都是现在的最小值，s1s2同时pop顶部元素，如果不等，只pop s1,从而可以找到次小值
 5.top方法为执行s1的顶部元素

 问题：
 1.不明白为什么答案里面声明stack都要先声明private
 2.不明白test cases给出输入值的格式，找不到main函数
 3.不明白原题目中MinStack(){}的含义，及本题的数据结构
 */