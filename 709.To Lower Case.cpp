题意：把字符串中的所有大写字母转换成小写字母
方法一：TLE tolower()方法
遍历暴力进行转换
class Solution {
public:
    string toLowerCase(string str) {
        for(int i = 0; i < str.size(); ++i){
            char temp = tolower(str[i]);
            str[i] = temp;
        }
        return str;
    }
};
方法2:ASCII码方法
思路：
1.因为A-Z的ASCII码是65-90，而a-z的ASCII码是97-122，正好相差32，所以利用ASCII码相加即可
2.注意因为是字符形式，所以判断的时候要是字符，数字的值直接相加即可
注意：
1.因为需要改变遍历到的字符的值，因此要用&符号
class Solution {
public:
    string toLowerCase(string str) {
        for(auto &s : str){
            if(s >= 'A' && s <= 'Z') s += 32;
        }
        return str;
    }
};
如果不记得ASCII码。先减去'A'再加上'a'即可。注意此处也要是字符的形式。
class Solution {
public:
    string toLowerCase(string str) {
        for(auto &s : str){
            if(s >= 'A' && s <= 'Z') s = s-'A'+'a';
        }
        return str;
    }
};