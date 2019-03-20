题意：
以空格为间隔反转字符串
思路：
1.用一个变量记录下来起始的位置，i进行遍历，遇到空格进行反转。
注意reverse()方法的两个变量值是起始位置和结束位置的下一位，因此是s.end()以及s.begin()+i的位置，不需要-1
注意：
1.要注意处理最后一个需要反转的字符串的位置，因为没有空格了，要到结尾之间的长度进行反转
class Solution {
public:
    string reverseWords(string s) {
        int j = 0;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == ' '){
                reverse(s.begin()+j,s.begin()+i);
                j = i+1;
            }
        }
        reverse(s.begin()+j,s.end());
        return s;
    }
};