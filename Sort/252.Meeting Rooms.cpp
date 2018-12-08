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


12.7复习
注意：
1.自定义排序方法的时候注意sort()方法中要写清楚cmp(),但是overload结构体的时候只写cmp
2.结构体里面定义operator()方法。方法的变量是需要比较的对象，const有无均可，但是如果是外部变量必须是&
返回的结果如果想从小到大就是小于号，如果从大到小就是大于号。
如果不用排序需要判断的是如果前一个数组的头部小于等于后一个数组的头部且前一个数组的尾部大于后一个数组的头部返回false.还需要交换判断一次。
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
        bool operator()(Interval a ,Interval b){
            return a.start < b.start;
        }
    };
    bool canAttendMeetings(vector<Interval>& intervals) {
        sort(intervals.begin(),intervals.end(),cmp());
        for(int i = 1; i< intervals.size();++i){
            if(intervals[i].start < intervals[i-1].end){
                return false;
            }
        }
        return true;
    }
};
