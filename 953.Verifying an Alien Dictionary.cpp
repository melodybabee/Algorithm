题意：
给一串字母排序，判断数组中的单词是否是按这个顺序排序的。
思路：
1.因为要对数组进行查找操作，判断其是否满足自定义的顺序，所以首先把自定义的字符串放在hashtable中，key是字符，value是其在字符串中的位置。
2.开始循环数组，从第一位开始比较，如果前面大直接返回false.
如果相等判断长度，取小，对这两个单词进行循环，如果前面大返回false,如果后面大跳出内循环，标志位为ture。
如果跳出内循环但是标记位没有变化，那么判断是否后面到结尾而前面没有，如果是，那么返回false,否则继续进入循环。
3.如果结束循环没有返回false,那么返回true.
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char,int>map;
        if(words.size() == 1) return true;
        for(int i = 0; i< order.size();++i){
            map[order[i]] = i;
        }
        for(int i = 1; i < words.size();++i){
            if(map[words[i][0]] < map[words[i-1][0]]) return false;
            if(map[words[i][0]] == map[words[i-1][0]]){
                int length1 = words[i].size();
                int length2 = words[i-1].size();
                int n = min(length1,length2);
                int j = 1;
                bool flag = false;
                for(j = 1; j < n;++j){
                    if(map[words[i][j]] < map[words[i-1][j]]) return false;
                    if(map[words[i][j]] > map[words[i-1][j]]) {
                        flag == true;
                        break;
                    }
                }
                if(flag == false){
                    if(j == words[i].size() && j < words[i-1].size()) return false;
                }
            }else continue;
        }
        return true;
    }
};

优化：
1.也可以用一个int,int 型的unordered_map来记录，把每个字符都转换成数字，最后判断字符串是否是排序好的
注意：
1.is_sorted()方法可以判断变量是否是排序好的
2.在循环时因为要更改字符为数字，所以如果用auto循环的话需要用&符号
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<int,int>map;
        if(words.size() == 1) return true;
        for(int i = 0; i< order.size();++i){
            map[order[i]-'a'] = i;
        }
        for(auto &s:words){
            for(auto &c : s){
                c = map[c-'a'];
            }
        }
        return is_sorted(words.begin(),words.end());
    }
};

Weekly contest114 总结
1.现在做题看完题意之后先会分析有什么特点应该用什么数据结构解决，好事，坚持。
2.第二题没有想到很理想的数学方法，第三题审题有问题感觉思路没问题但test case过不了，还要多练。
3.把不熟悉的数据结构，图、trie、拓扑排序、01背包问题好好加强，不能一看是图的问题就不思考了。