题意：
找出给出的时间中的几个数字组成的下一个时间。
思路1：
1.要找到下一位时间那么在00:00之前的时间需要比给出的大，或者找到第二天的最小时间
2.首先把给出的时间放在一个set中，去重同时排序，再把排序好的数字转换成string形式便于循环
3.首先从给出时间的最后一位开始判断，找到这个数字在数组中的位置，如果这个数组在数组中位于最后一位，没有比它大的数字了，那么直接改写成最小值
4.如果不是最后一位，首先设置一个标记值记录下这位数字在数组中的下一位值
如果这个数字在分钟低位，那么可以直接更换
如果这个数字在分钟高位，需要判断是否小于等于5，是更换，不是更改为最小位
如果这个数字在小时地位，那么需要判断小时高位是否是2，如果是，那么需要小于等于3，如果不是，可以自由更换
如果这个数组在小时高位，那么需要小于等于2
5.如果以上有不满足条件的，就替换位最低位。因为最低位一定是0，1，2之内的数字，满足条件。
6.最后返回原字符串即可。
注意：
1.set转换为string，直接写明字符串名称，把set的数字从头到尾放入即可。string s(set.begin(),set.end())。
2.如何在一个字符串中找到一个字符的位置，int pos = s.find(time[i]);返回的事time[i]这个字符在s中的位置。
class Solution {
public:
    string nextClosestTime(string time) {
        set<int> set{time[0],time[1],time[3],time[4]};
        string s(set.begin(),set.end());
        for(int i = time.size()-1; i >= 0; --i){
            if(time[i] == ':') continue;
            int pos = s.find(time[i]);
            if(pos == s.size()-1) time [i] = s[0];
            else{
                char next = s[pos+1];
                if(i == 4) {
                   time[i] = next;
                   return time;
                }else if(i == 3 && next <= '5'){
                    time[i] = next;
                    return time;
                }else if(i == 1 && (time[0] != '2' || time[0] == '2' && next <= '3')){
                    time[i] = next;
                    return time;
                }else if(i == 0 && next <= '2'){
                    time[i] = next;
                    return time;
                } 
                time[i] = s[0];
            }
        }
        return time;
    }
};
思路2:
【用1440个时间点的方法需要学习】