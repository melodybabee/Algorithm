题意：
找到string中第一个只出现一次的元素
思路：
1.建立hashtable,key中放元素，value放出现次数
2.首先循环一遍把每个字符都放到map中，学会使用自动循环for(auto c: s)，无需再重新声明类型
3.再重新循环string,如果找到出现次数为1的位置，直接输出
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char,int>map;
        for(auto c: s) ++map[c];
        for(int i = 0; i < s.size(); ++i){
            if(map[s[i]] == 1)
                return i;
        }
        return -1;
    }
};

优化：
如果不想用map,想直接使用vector的话，需要把字母转换为26进制数字的思路
注意：
1.如果想使用vector的index，必须在最初声明的时候就标号大小
2.注意在第二个for循环中，仍然需要从string的第一位开始判断，因为想要找的是第一个出现一次的元素
class Solution {
public:
    int firstUniqChar(string s) {
        vector<int> vec(26,0);
        for(int i = 0; i< s.size(); ++i){
            vec[s[i] - 'a']++;
        }
        for(int i = 0; i < s.size(); ++i){
            if(vec[s[i] - 'a'] == 1) return i;
        }
        return -1;
    }
};