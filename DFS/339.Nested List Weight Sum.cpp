Nested 嵌套的
题意：
一个数组由很多个嵌套的子数组组成，每嵌套一层层数+1，求数组中的权重和。
思路：
1.因为数组中有数字，有不同层次的嵌套，因此用递归DFS判断，从而求出所有的权重和。
2.首先在主函数中遍历，每遍历到一个结点调用递归，用一个值记录下所有结点的和。
3.进入递归函数之后，如果是整数，直接用整数的值*层数相加
4.如果不是整数，遍历层数，调用递归
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        int ret = 0;
        for(auto nest : nestedList){
            ret += get(nest,1);
        }
        return ret;
    }

    int get(NestedInteger n, int level){
        int ret = 0;
        if(n.isInteger()) return n.getInteger() * level;
        for(auto nest : n.getList()){
            ret += get(nest, level+1);
        }
        return ret;
    }
};

优化：
写成一个递归。在递归函数中判断即可。
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        int ret = helper(nestedList,1);
        return ret;
    }
    
    int helper(vector<NestedInteger>& nestedList,int level){
        int ret = 0;
        for(auto nest : nestedList){
            ret += nest.isInteger() ? nest.getInteger() * level : helper(nest.getList(), level+1);
        }
        return ret;
    }
};

12.13复习：
注意：
DFS思想因此需要记录下来level层数，再在递归函数中进行遍历。
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        int level = 1;
        return helper(nestedList,level);
    }
    
    int helper(vector<NestedInteger>& nestedList,int level){
        int ret = 0;
        for(auto nest : nestedList){
            ret += nest.isInteger() ? nest.getInteger()*level : helper(nest.getList(), level +1);
        }
        return ret;
    }
};

3.17复习
注意：
1.如何取到每一层，判断是数字还是list,用DFS+递归进行遍历，如果是数字就直接相乘，如果是list就进入递归
注意此处的递归方法
2.进入递归之后level自动+1
3.注意给出的方法，用遍历到的nest依次通过.进行调用
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        int level = 1;
        return helper(nestedList, level);
    }
    
    int helper(vector<NestedInteger>& nestedList, int level){
        int ret = 0;
        for(auto nest : nestedList){
            if(nest.isInteger()) ret += level * nest.getInteger();
            else ret += helper(nest.getList(), level+1);
        }
        return ret;
    }
};

补充：
C++中箭头引用和点引用的区别
对于一个c++结构来说：
struct MyStruct
{ 
      int member_a; 
};
如果有个变量MyStruct s，那么使用其中的成员元素时可以用
s.member_a = 1;
如果采用指针方法访问，比如 MyStruct * ps，那么同样的访问就必须使用如下形式：
(*ps).member_a = 1;或者ps->member_a = 1;
即如果想用.的话需要把指针类型做取值操作，改为实体
箭头（->）：左边必须为指针； 
点号（.）：左边必须为实体。
