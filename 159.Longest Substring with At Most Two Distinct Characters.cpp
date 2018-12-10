题意：
找到字符串中只包含2个数字的最长子字符串。
方法1:HashTable
思路：
1.循环字符串，每循环到一位在map中加入一对映射，如果map中的数量大于2，那么从左边界开始删减。
每次在map的value中删减1，如果map中的value值为0，那么删除它的key.直到map中的大小等于2为止。
移动左边界到满足条件的下一位。
2.结果值记录的是结果值和当前坐标与左边界之间的距离+1。
3.返回结果值。
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char,int>map;
        int left = 0;
        int ret = 0;
        for(int i = 0; i< s.size() ;++i){
            ++map[s[i]];
            while(map.size() > 2){
                --map[s[left]];
                if(map[s[left]] == 0) map.erase(s[left]);
                ++left;
            }
            ret = max(ret,i-left+1);
        }
        return ret;
    }
};