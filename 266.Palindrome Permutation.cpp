题意：判断一个乱序的字符串是否能是回文的
思路：
1.用一个hashmap计数，再遍历hashmap判断是否是偶数，只能有一个奇数的机会。因此最后判断返回的值是否小于等于1.
class Solution {
public:
    bool canPermutePalindrome(string s) {
        if(s.empty()) return true;
        unordered_map<char,int>map;
        for(auto c: s){
            ++map[c];
        }
        int count = 0;
        for(auto m : map){
            if(m.second % 2 != 0){
                ++count;
            }
        }
        return count <= 1;
    }
};