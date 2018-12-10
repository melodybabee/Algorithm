题意：
159 follow up,找到字符串中最多出现K次的最长字串长度。
思路：
1.同样用一个unordered_map来记录字符出现的次数，如果map的大小大于k,那么从左边界map中对应的key的value值减1.
如果value等于0，那么删除该key.左边界右移。
结果值记录下当前值和当前坐标到左边界之间距离的较大值。
注意：
1.求子串通常会用到左边界，因为子串需要保证连续，如果截取也是从左到右依次截取，不会跳跃。
2.map.size()能找到map中有多少个key.
3.map.erase()删除map中的key-value对。
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char,int>map;
        int left = 0;
        int ret = 0;
        for(int i = 0; i < s.size(); ++i){
            ++map[s[i]];
            while(map.size() > k){
                --map[s[left]];
                if(map[s[left]] == 0) map.erase(s[left]);
                ++left;
            }
            ret = max(ret,i-left+1);
        }
        return ret;
    }
};