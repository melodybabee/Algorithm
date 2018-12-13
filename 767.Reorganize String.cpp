题意：重新安排字符串，使得其没有连续相同的相邻字符。
思路：
1.首先需要明确，只要字符串中出现了大于其长度一半的字符数量，那么不可能形成穿插的字符串，那么直接返回空即可。
2.首先用一个map记录下每个字符出现的频率，然后对于出现的次数为key输入到优先队列中去。
3.开始从heap中取值，每次取两个，作为返回值返回在字符串中，如果取出之后还有剩余那么返回heap中
4.如果最后heap中仍有剩余，那么把剩余元素输出，最后返回字符串
class Solution {
public:
    string reorganizeString(string S) {
        string ret = "";
        unordered_map<char,int>map;
        for(auto a:S) ++map[a];
        priority_queue<pair<int,char>>q;
        for(auto it : map){
            if(it.second > (S.size()+1)/2) return ret;
            q.push({it.second,it.first});
        }
        
        while(q.size()>=2){
            auto q1 =q.top();
            q.pop();
            auto q2 = q.top();
            q.pop();
            ret += q1.second;
            ret += q2.second;
            --q1.first;
            --q2.first;
            if(q1.first>0) q.push(q1);
            if(q2.first>0) q.push(q2);
        }
        if(!q.empty()) ret += q.top().second;
        return ret;
    }
};