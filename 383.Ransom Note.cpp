Ransom 循环的，赎回的。
题意：判断某一个字符串是否可以由另一个字符串重建组成。
思路：
1.建立一个哈希表把源数组输入进去，遍历目标数组，每遇到一个字符就在对应的map上面-1。
一旦某个位置上的值小于0，直接返回false。如果遍历结束还没有返回false,返回true。
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char,int>map;
        for(auto m : magazine){
            ++map[m];
        }
        for(int i = 0; i < ransomNote.size(); ++i){
            --map[ransomNote[i]];
            if(map[ransomNote[i]] < 0) return false;
        }
        return true;
    }
};