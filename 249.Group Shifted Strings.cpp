题意：
给了一组单词，把是偏移字符串的放在一组。
偏移字符串就是一个字符串的每个字符按照字母顺序表偏移相同量得到的另一个字符串，两者互为偏移字符串。
相同字符串是偏移字符串的一种特殊情况，偏移量为0。
049follow up.
思路:
1.本来觉得和049是完全大同小异的题目，没有注意偏移量这个条件，直接把一样长度的放在一组，那么"ab"和"ba"就是不同偏移量，不应该放在一组，要注意审题。
2.那么建立一个hashtable,key是一个字符串记录下每个字符之间的偏移量,形成字符串；value是存有相同偏移量单词的数组
3.最后再遍历map，输出第二个元素
注意
在求偏移量的时候用str[i] - str[0]即为整数，类似a-'a' = 0,把字符转换为int 型
同时因为求的是绝对值，比如za和ab是属于同偏移量的，因此+26再取余得到的就是正值
class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        vector<vector<string>> ret;
        unordered_map<string,vector<string>> map;
        for(auto &str : strings){
            int len = str.size();
            string temp = str;
            for(int i = 0; i < len; ++i){
                temp[i] = (str[i] - str[0] + 26) % 26;
            }
            map[temp].push_back(str);
        }
        for(auto m : map){
            ret.push_back(m.second);
        }
        return ret;
    }
};