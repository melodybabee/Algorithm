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