题意：
对应给出的字符串的增减写出规定范围内的数字表示。
思路：
1.要求输出0-给定数组长度范围内的所有数字，输出的顺序按照原数组，I表示下一位大于当前位，D表示下一位小于当前位
2.通过观察发现如果是增，那么从0开始输出数字，如果是减，从尾部最大元素开始输出数字一定能满足题目中的情况。
3.注意因为输出的数组要比原有的数组的长度大1，因此在最后还应该加上最后一位，此时begin和end相等
4.输入新的数组即可
注意：讨论区给出的此方法称为Ad-Hoc，即为输出指定的字符。
class Solution {
public:
    vector<int> diStringMatch(string S) {
        vector<int>ret(S.size()+1);
        int begin = 0;
        int end = S.size();
        for(int i = 0 ;i < S.size(); ++i){
            if(S[i] == 'I'){
                ret[i] = begin;
                ++begin;
            }else{
                ret[i] = end;
                --end;
            }
        }
        ret[S.size()] = begin;
        return ret;
    }
};