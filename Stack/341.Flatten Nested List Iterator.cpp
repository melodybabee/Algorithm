题意：设计一个结构能够把嵌套在内的数字一个一个输出。
思路：
1.设计一个栈，利用栈后进先出的性质，从后面开始逐个push进来
2.判断是否有下一位的时候，如果栈顶是正数，那么返回true
如果是嵌套类型的，那么首先pop()出来，接着从尾部开始循环，再依次push进去
注意擅用给的interface,onst vector<NestedInteger> &getList() const;为获取嵌套结构，是一个vector类型
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
private:
    stack<NestedInteger>st;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(int i = nestedList.size()-1; i >= 0; --i){
            st.push(nestedList[i]);
        }
    }

    int next() {
        NestedInteger temp = st.top();
        st.pop();
        return temp.getInteger();
    }

    bool hasNext() {
        while(!st.empty()){
            NestedInteger temp = st.top();
            if(temp.isInteger()) return true;
            st.pop();
            for(int i = temp.getList().size()-1; i >= 0; --i){
                st.push(temp.getList()[i]);
            }
        }
        return false;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */