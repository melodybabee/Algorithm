题意：
339 follow up,最外层的层数最大，最内层为1，求出所有数字的权重。
思路1:DFS
1.因为不知道层数是多少，所以首先调用一个DFS求出层数的深度。如果是整数，返回当前值的较大值。如果不是数字，那么调用递归+1值与现在的较大值。
2.再通过层数递减来求出所有值的和。
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
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int ret = 0;
        int level = findLevel(nestedList);
        ret = helper(nestedList,level);
        return ret;
    }
    int findLevel(vector<NestedInteger>& nestedList){
        if(nestedList.empty() || nestedList.size() == 0) return 0;
        int level = 0;
        for(auto nest : nestedList){
            if(nest.isInteger()) level = max(level,1);
            else {
                level = max(level, findLevel(nest.getList())+1);
            }
        }
        return level;
    }
    
    int helper(vector<NestedInteger>& nestedList, int level){
        int ret = 0;
        for(auto nest : nestedList){
            ret += nest.isInteger() ? nest.getInteger() * level : helper(nest.getList(), level-1);
        }
        return ret;
    }
};
方法二：
1.一次遍历，因为数字相加的次数最多，所以每次遍历过滤出数字，单独相相加，把其他的数组保存起来
2.再次进入遍历的时候开始计算之前被保存进去的数组，这样数字加的次数就为它的层数
注意：
保存在数组中需要把其最外层的壳去掉，因此需要从数组的尾部开始，insert原数组的头部到原数组的尾部的元素。
每次把当次遍历求得的和加到结果值中，临时数组更新为原数组。
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
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int ret = 0;
        int temp = 0;
        while(!nestedList.empty()){
            vector<NestedInteger> list;
            for(auto nest : nestedList){
                if(nest.isInteger()) temp += nest.getInteger();
                else{
                    list.insert(list.end(),nest.getList().begin(),nest.getList().end());
                }
            }
            ret += temp;
            nestedList = list;
        }
        return ret;
    }
};