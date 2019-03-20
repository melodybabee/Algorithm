题意：
找到一个字符串中出现的次数最多的单词，但是需要排除数组中出现的单词
思路：
1.首先利用哈希表用来保存字符串中出现的单词。
单词的划分是在遍历的过程中，首先判断是否是字母，再全部转换成小写，所以只要是字母的话就一直进行while循环。
如果不是字母的话要一直while循环跳过。
注意因为跳过的部分坐标一直增加，那么在结束while循环之后需要把指针-1.
2.处理之后把处理好的单词放入map中，在数组中出现过的单词需要在map中设置为0
3.最后找到map中value值最大的那个。应该也可以对map的value进行排序，但是直接暴力查找也可以得到最终结果。
class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        unordered_map<string,int>map;
        for(int i = 0; i < paragraph.size(); ++i){
            string temp;
            while(i < paragraph.size() && isalpha(paragraph[i])){
                temp += tolower(paragraph[i]);
                ++i;
            }
            while(i < paragraph.size() && !isalpha(paragraph[i])){
                ++i;
            }
            --i;
            ++map[temp];
        }
        for(auto word : banned){
            map[word] = 0;
        }
        int count = 0;
        string res;
        for(auto it : map){
            if(it.second > count){
                res = it.first;
                count = it.second;
            } 
        }
        return res;
    }
};