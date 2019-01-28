题意：
给出员工的工作时间，求出所有员工的空闲时间。
方法一：merge
思路：
1.因为在原数组中是Interval的类型，那么首先把所有的内嵌的Interval先拿出来，放到一个vector中进行排序
2.接下来和merge数组的思路一样，后面的数字的第一个数如果大于前面数字的第二个值，那么说明中间有空隙，那么直接插入到返回数组中
如果有重叠部分，哪个的第二个数字大取哪个的值
注意：
善于运用排好序的数组，因为已经排好序，那么第一个数字的大小已经确认，后面的数字的第一个数字的大小是大于等于前面数字的，因此在有重叠部分的时候可直接应用
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
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
        vector<Interval>ans;
        vector<Interval>temp;
        for(auto s : schedule){
            temp.insert(temp.end(),s.begin(),s.end());
        }
        sort(temp.begin(),temp.end(),[](Interval &a, Interval &b){
            return a.start < b.start;
        });
        Interval cur = temp[0];
        for(auto t : temp){
            if(t.start > cur.end){
                ans.push_back({cur.end,t.start});
                cur = t;
            }else{
                cur = t.end > cur.end ? t : cur;
            }
        }
        return ans;
    }
};
方法2:利用map进行坐标轴自动排序
思路：
1.因为map有自动排序的功能，会把数字从小到大排列，所以可以模拟坐标轴
2.遍历原数组中的左右的区间，区间中的第一个数字在map中+1，第二个数字在map中-1
3.所以在map中value的正数表示一段区间的开始，负数表示结束。用一个变量来记录，如果正负相加等于0，那么说明现在是一段区间的结束，在结果数组中记录下这个位置
如果当前不为0，且结果数据中的前一位是0，那么表示有间隔产生，更新即可
4.因为最后会push进去{最后一位，0}，所以在输出之前还需要pop_back()
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
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
        map<int,int>m;
        vector<Interval>ans;
        for(auto s : schedule){
            for(auto i : s){
                ++m[i.start];
                --m[i.end];
            }
        }
        int temp = 0;
        for(auto j : m){
            temp += j.second;
            if(temp == 0) ans.push_back({j.first,0});
            if(temp != 0 && !ans.empty() && ans.back().end == 0) ans.back().end = j.first;
        }
        ans.pop_back();
        return ans;
    }
};