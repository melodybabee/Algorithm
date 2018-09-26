思路：
1.本文用queue来模拟stack的方法，比如top()应该输出最后一个进入的元素，而不是第一个
2.在push方法里设置一个临时的queue,把已有的queue中的元素先依次从头部插入到临时的queue中
3.已有的queue中永远放最后一个新插入的值，再把temp中已有的所有数值push到已有的queue中
注意：
1.queue.front()是输出queue的第一个元素

class MyStack {
private:
    queue<int> q;

public:
    /** Initialize your data structure here. */
    
    /** Push element x onto stack. */
    void push(int x) {
        queue <int> temp;
        while(!q.empty()){
            temp.push(q.front());
            q.pop();
        }
        q.push(x);//queue本身的push方法
        while(!temp.empty()){
            q.push(temp.front());
            temp.pop();
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int ret = q.front();
        q.pop();
        return ret;
    }
    
    /** Get the top element. */
    int top() {
        return q.front();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q.empty();
    }
};

