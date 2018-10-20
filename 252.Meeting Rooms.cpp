题意：
判断所有子区间有没有冲突
思路：
1.首先对所有区间的头结点进行排序，之后for循环以此遍历
2.如果后一个的头结点小于当前位置的尾部结点，就是有重复,false，如果循环结束还没有重复，那么true
注意：
1.还是要注意复写sort()的排序方法，不够熟练
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
    struct intervalSort{
        bool operator()(const Interval &c1, const Interval &c2){
            return c1.start < c2.start;
        }
    };
    bool canAttendMeetings(vector<Interval>& intervals) {
        if(intervals.empty()) return true;
        sort(intervals.begin(),intervals.end(),intervalSort());
        for(int i = 0; i < intervals.size()-1; ++i){
            if(intervals[i].end > intervals[i+1].start) return false;
        }
        return true;
    }
};
法2:两个for循环也能解决问题：
重叠的情况是前一位的头<=后一位的头但是前一位的尾>后一位的头，就是重叠。反之亦然。
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
    bool canAttendMeetings(vector<Interval>& intervals) {
        for(int i = 0; i < intervals.size();++i){
            for(int j = i+1; j < intervals.size(); ++j){
                if((intervals[i].start <= intervals[j].start && intervals[j].start < intervals[i].end) ||(intervals[j].start <= intervals[i].start && intervals[i].start < intervals[j].end))
                    return false;
            }
        }
        return true;
    }
};