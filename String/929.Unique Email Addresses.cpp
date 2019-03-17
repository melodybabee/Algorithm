题意：
找到有效的邮件地址个数，如果有'.'跳过，如果有'+'直接到@位置
思路：
1.因为要有去重的判断，因此本题用到了hashtable的数据结构
2.首先处理字符串：
创建一个新的string来记录结果，先循环所有的邮件地址，在@之前如果等于'.'直接跳过到下一位；如果等于'+'，直接移动到@位置之前，break
否则在新的字符串中添加上这一位字符，判断完成后把@后面的所有字符加在新字符串后面。
3.把新的字符串在map中查找，如果不存在存入map中，存在就跳过
4.最后循环map,输出map.second的值的和
class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_map<string,int>map;
        int count = 0;
        int i = 0;
        int j = 0;
        for(auto &s : emails){
            string str = "";
            for(i = 0; s[i] != '@';++i){
                if(s[i] == '.') continue;
                if(s[i] == '+') {
                    while(s[i] !='@'){
                        ++i;
                    }
                    break;
                }
                else{
                    str += s[i];
                }
            }
            str += s.substr(i,s.size()-1);
            if(map.find(str) == map.end()) ++map[str];
        }
        
        for(auto m :map){
            count += m.second;
        }
        return count;
    }
};
优化：
可以用到unordered_set的数据结构，这样直接insert进去之后，会自动去重，最后输出set的大小(int)set.size()即可。

Contest 108总结：
1.本次AC两题，结束后把第三题AC了，1600+
2.第一题一个easy题花了将近半个小时，首先心态上有点轻敌，后面在各种边界条件上停了很久。
想到用什么方法想清楚就立刻动手写，不要受题目难度干扰而留下关于难度第一印象。
做完第一题看了一下排名，已经有人完赛，第一题耗时3分钟，想不到一个循环+map+边界条件的题目连想带写3分钟结束，自己数据结构的书写和应用还差的太远了。
3.第二题本身是一次性思路没问题的，但是TLE，所以比赛中剩下的时间都在为了换一种新的方法。
这道题有更多没有考虑清楚的边界条件，后来看实在没时间了就用提交界面debug,排答对两题的倒数3名。有7次罚时。
4.第三题用到了前两天刚刚刷到的自下而上DP，思路没问题，但是操作起来和原题不同的地方开始没有思考清楚，后来改了半天。
5.平时刷题如果看别人的思路，一定要从头到尾自己过一遍思路，自己背着写，不要写一点看一点。
就算思路能记起来，很多边界条件也想不清楚，要提高对corner cases的重视程度！！！
对于一些模版题和模版思路的代码要不断重复并默写，不要在这些套路上耽误时间。
思路和熟练度是必须通过大量刷题练习的，目前量的积累>重复思路，快刷！多刷！突破瓶颈，兼顾复习。

3.16复习：
注意：
1.因为需要返回的是所有去重后的字符串的个数，因此用set能直接解决这个问题，最后返回set的长度即可
2.依次处理每个字符串，分别处理每种情况。如果是.跳过，如果是+，直接跳到@的位置，如果到了@那么把结尾部分直接相加，注意如果是前半部分的普通情况那么加入到字符串中
3.处理后将每个字符串输入到set中
class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_set<string>set;
        for(auto e : emails){
            string temp = "";
            for(int i = 0; i < e.size(); ++i){
                if(e[i] == '.') continue;
                if(e[i] == '+') {
                    while(e[i] != '@') ++i;
                }
                if(e[i] == '@'){
                    temp += e.substr(i);
                    break;
                }
                temp += e[i];
            }
            set.insert(temp);
        }
        return set.size();
    }
};

