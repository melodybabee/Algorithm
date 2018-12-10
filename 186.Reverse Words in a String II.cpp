题意：
151 follow up。翻转字符串。
思路：
1.和151一样先反转全部的字符串，再逐个反转，根据中间的空格来判断单词的结尾。
class Solution {
public:
    void reverseWords(vector<char>& str) {
        reverse(str.begin(),str.end());
        for(int i = 0 ; i < str.size(); ++i){
            int j = i;
            while(j < str.size() && str[j] != ' ') ++j;
            reverse(str.begin()+i,str.begin()+j);
            i = j;
        }
    }
};
