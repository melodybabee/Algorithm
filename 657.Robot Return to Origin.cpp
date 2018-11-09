题意：
找到机器人能否回到起点，左右匹配&上下匹配。
思路：
1.用一个unorder_map存储字符的数量，如果左和右的数量相等，上和下的数量相等，那么true,否则false
2.在比较map的个数的时候直接判断某位是否等于某位即可，直接代表的是数量。
class Solution {
public:
    bool judgeCircle(string moves) {
        unordered_map<char,int>map;
        for(int i= 0; i< moves.size();++i){
            ++map[moves[i]];
        }
        return map['U'] == map['D'] && map['L'] == map['R'];
      
    }
};
