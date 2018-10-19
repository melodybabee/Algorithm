题意：
给一个数组和一个需要插入的值，找到应该插入的位置，并去掉重复的部分
方法1:while循环
思路：
1.首先用while循环判断是否有重合的部分，如果原数组的尾部大于新数组的头部，那么没有重合的部分，直接push即可
2.当从上一个while循环中跳出之后便表示有重合的部分，那么即intervals[i].end >= newInterval.start,所以要比较第一个数组的头部和第二个数组的尾部
把新数组的头部更新为两个数组头部元素中的较小值，尾部元素更新为两个数组尾部元素中的较大值
3.如果是新数组在原两个数组之间的空隙而没有重合部分，那么直接把新数组push进入即可
4.当跳出这个循环之后表示没有重复的部分了，那么把新的数组push到ret中
5.ret的后面加上原数组中没有循环到的部分
注意：
1.本题中的i一直在循环原vector,因此表示的是原数组的顺序
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval>ret;
        int i = 0;
        while(i < intervals.size() && intervals[i].end < newInterval.start){
            ret.push_back(intervals[i]);
            ++i;
            }
        while(i < intervals.size() && intervals[i].start <= newInterval.end){
            newInterval.start = min(intervals[i].start, newInterval.start);
            newInterval.end = max(intervals[i].end,newInterval.end);
            ++i;
        }
        ret.push_back(newInterval);
        while(i < intervals.size()){
            ret.push_back(intervals[i]);
            ++i;
        }
        return ret;
    }
};
改用for循环的代码（思路大致相同，但是注意新数组的insert位置）：
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> ret;
        int cur = 0;
        for(int i = 0; i< intervals.size();++i){
            if(intervals[i].end < newInterval.start){
                ret.push_back(intervals[i]);
                ++cur;
            }else if(intervals[i].start > newInterval.end){
                 ret.push_back(intervals[i]);
            }else{
                newInterval.start = min(intervals[i].start,newInterval.start);
                newInterval.end = max(intervals[i].end,newInterval.end);
            }
        }
        ret.insert(ret.begin()+cur,newInterval);
        return ret;
    }
};
