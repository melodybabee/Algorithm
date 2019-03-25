题意：反转字符串中的元音字母
思路：
1.two pointers分别从后先前和从前向后扫描
2.注意在while扫描的过程中也需要保证l<r,同时交换之后要继续++l,--r
class Solution {
public:
    string reverseVowels(string s) {
        int l = 0;
        int r = s.size()-1;
        while(l < r){
            while(s[l] != 'a' && s[l] != 'e' && s[l] != 'i' && s[l] != 'o' && s[l] != 'u' && s[l] != 'A' && s[l] != 'E' && s[l] != 'I' && s[l] != 'O' && s[l] != 'U'  && l < r){
                ++l;
            }
            while(s[r] != 'a' && s[r] != 'e' && s[r] != 'i' && s[r] != 'o' && s[r] != 'u' && s[r] != 'A' && s[r] != 'E' && s[r] != 'I' && s[r] != 'O' && s[r] != 'U'  && l < r){
                --r;
            }
            swap(s[l],s[r]);
            ++l;
            --r;
        }
        return s;
    }
};
优化：
为了避免重复的写出10个元音字母，可以首先建立一个数组int dict[256] = {0};，一共ASCII码256个位置，把所有的元音字母更换为1，判断如果等于0就一直移动
注意更改为1的时候要为字符的形式
dict['a'] = 1, dict['A'] = 1;
dict['e'] = 1, dict['E'] = 1;
dict['i'] = 1, dict['I'] = 1;
dict['o'] = 1, dict['O'] = 1;
dict['u'] = 1, dict['U'] = 1;