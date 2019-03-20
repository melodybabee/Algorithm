题意：
以2k为一组反转前k个字符
思路：
1.注意处理最后的尾部部分的字符串。因为题目中的要求是如果最后在k以内那么全部反转，如果在k-2k之间那么反转前k个字符
2.所以以2k为一组不断增加i的坐标，如果尾部的位置到i的长度小于k了，那么把尾部的字符串反转直接break即可
3.否则就按照正常情况处理反转前k部分，再把后半部分k接上即可
class Solution {
public:
    string reverseStr(string s, int k) {
        int length = s.size();
        //if(k > length) return s;
        string ret = "";
        for(int i = 0; i < s.size(); i += 2*k){
            if(length-i < k){
                string temp = s.substr(i);
                reverse(temp.begin(),temp.end());
                ret += temp;
                break;
            }
            string temp = s.substr(i,k);
            reverse(temp.begin(),temp.end());
            ret += temp;
            ret += s.substr(i+k,k);
        }
        return ret;
    }
};
优化：
因为k-2k的部分是不会被反转的，因此如果是正常的反转，那么反转前k部分即可。如果是长度小于k的，那么直接反转到结尾的所有长度即可。
class Solution {
public:
    string reverseStr(string s, int k) {
        for(int i = 0; i < s.size(); i += 2*k){
            if(i + k < s.size()) reverse(s.begin()+i,s.begin()+i+k);
            else reverse(s.begin()+i,s.end());
        }
        return s;
    }
};