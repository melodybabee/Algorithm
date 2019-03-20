class Solution {
public:
    string reverseString(string s) {
        string ret = "";//不给ret赋值"",ret也默认为空字符串
        if(s == "") return "";//不写这一行也可以，因为如果s是空字符串，不会进入for循环，直接会return ret,ret也是一个空字符串
        for (int i = s.size()-1; i >= 0; --i){
            ret += s[i];
        }
        return ret;
        
    }
};


/*
AC率60%+的题，不一次性写对就说不过去了
优化算法：
std::reverse(s.begin(), s.end());
用到了上述方法，待学习

*/


3.19复习
需要O（1）的空间复杂度，双指针的标准题。注意swap之后不然忘了移动指针。
class Solution {
public:
    void reverseString(vector<char>& s) {
        int l = 0;
        int r = s.size()-1;
        while(l < r){
            swap(s[l],s[r]);
            ++l;
            --r;
        }
    }
};