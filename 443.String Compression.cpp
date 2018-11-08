题意：
把重复的字符串进行压缩。
思路：
1.首先循环字符串，如果下一位与当前位不等，那么把当前位更新到新的字符串中去。
2.如果只有一个，不需要加入数字，因此如果是1个字符，直接进行到下一位即可。
如果大于1个，那么循环到的位置会大于当前位，需要记录下当前位置到最开始位置的长度，因为是数字，需要转换为string类型。
如果为10以上的数字，会不止一位，因此还要对string进行循环来输出数字，更新到数组里。
3.再把len更新到当前位置+1，即下一轮循环应该记录的位置。
4.最后返回新数组的长度。但是编译器会产生新的替换过的数组。
class Solution {
public:
    int compress(vector<char>& chars) {
        int ret = 0;
        int cur = 0;
        int len = 0;
        for(int i= 0; i < chars.size(); ++i){
            if(i+1 == chars.size() || chars[i+1] != chars[i]){
                chars[cur] = chars[i];
                ++cur;
                if(len < i){
                    string s = to_string(i-len+1);
                    for(char c:s){
                    chars[cur] = c;
                    ++cur;
                    }
                }
                len = i+1;
            }
        }
        return cur;
    }
};