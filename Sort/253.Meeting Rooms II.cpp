题意：
如果子数组中有重叠，那么就不能共用一间会议室，问一共需要多久间会议室
注意：
1.不能用先排序再循环的老方法，因为如果只根据前一个的尾节点和下一个的头结点来判断的话
遇到[4,7][4,17][7,9]的问题，实际需要2间会议室，但是输出是3间。因为头结点相同的情况下会有多个数组，但是后面的某个数组会与前面的尾部相连，那么实际上需要1间会议室。
方法一：map
思路：
1.用一个treemap记录下所有开始时间和结束时间，如果是开始时间就+1，如果是结束时间就-1
注意要用treemap而不是unordered_map因为map是有序的，在后面输出的时候会先输出正数（第一个肯定是正数），而散列表无序输出有可能是负数，不满足题意。
2.循环map,每次用room相加map.second位置的值，再返回与初始值相比较大的值。
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int,int>map;
        int ret = 0;
        for(auto &i : intervals){
            ++map[i.start];
            --map[i.end];
        }
        int room = 0;
        for(auto &i : map){
            ret = max(ret,room += i.second);
        }
        return ret;
    }
};
方法二：Chronological Ordering 按顺序排序，分成两个数组
T(n)=O(NlogN),S(n)=O(n);
思路：
1.分别把起始位置和终点位置push到两个数组中去，排序
2.从起点数组开始循环，如果小于终点数组的位置，表示需要一个房间，如果大于等于，则不需要，移动终点位置的数组
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
    int minMeetingRooms(vector<Interval>& intervals) {
        vector<int>start;
        vector<int>end;
        for(auto i : intervals){
            start.push_back(i.start);
            end.push_back(i.end);
        }
        int ret = 0;
        int j = 0;
        sort(start.begin(),start.end());
        sort(end.begin(),end.end());
        for(int i = 0; i < intervals.size();++i){
            if(start[i]<end[j]) ++ret;
            else{
                ++j;
            }
        }
        return ret;
    }
};
方法三：最小堆，Priority Queues
T(n)=O(NlogN),S(n)=O(n);
思路：
1.最小堆的方法非常好理解，借助C++内置函数实现从小到大的排序。
2.首先给数组按照起始时间排序，输入结束时间，如果后面的开始时间大于等于最小堆的头部元素，说明可以使用同一件会议室，那么弹出栈顶元素，输入新的结束时间
3.最后计算栈中的元素个数
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
    struct cmp{
        bool operator()(Interval a, Interval b){
            return a.start < b.start;
        }
    };
    int minMeetingRooms(vector<Interval>& intervals) {
        if(intervals.empty()) return 0;
        sort(intervals.begin(),intervals.end(),cmp());
        priority_queue<int,vector<int>,greater<int>>q;
        for(int i = 0; i < intervals.size();++i){
           if(!q.empty() && intervals[i].start >= q.top()) q.pop();
            q.push(intervals[i].end);
        }
        return q.size();
    }
};