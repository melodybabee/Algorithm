题意：
按照给出的字符串顺序排序原有的字符串。
方法一：Hashtable
思路：
1.首先用一个hashtable记录下S中字符出现的位置，key是位置，value是字符。
2.建立一个vector数组，遍历T,每当遍历到一个新的字符，循环map,看map的value中有没有这个字符，如果有，在数组中的对应key位置+1,没有就在临时字符串中记录下这个字符。
3.遍历数组，如果数组中的值不为0，表示在S中出现过这个字符，那么在结果字符串中添加数组值个该字符，字符从map中查找。
4.最后用结果数组+临时数组即可。
class Solution {
public:
    string customSortString(string S, string T) {
        unordered_map<int,char>map;
        vector<int>vec(T.size(),0);
        string ret;
        string temp;
        bool flag = false;
        for(int i = 0; i < S.size();++i){
            map[i] = S[i];
        }
        for(int i = 0; i < T.size();++i){
            flag = false;
            for(auto it:map){
            if(it.second == T[i]){
                ++vec[it.first];
                flag = true;
                }     
            }
            if(!flag)temp +=T[i];
        }
        for(int i = 0; i < vec.size();++i){
            if(vec[i] != 0)ret.append(vec[i],map[i]);
        }
        ret += temp;
        return ret;
    }
};
方法二：用hashmap记录T的频数，不是S
思路：
1.首先记录下T的频数，再遍历S，如果S中的字符在map中存在，那么结果字符串输出这个频次个字符。
把遍历过的字符的频数更改为0.
2.再遍历一遍map,把其他还有1次频数的字符输出在结果字符串后面。
class Solution {
public:
    string customSortString(string S, string T) {
        unordered_map<char,int>map;
        string str;
        for(auto t: T) ++map[t];
        for(auto s: S){
            if(map.count(s)) str.append(map[s],s);
            map[s] = 0;
        }
        for(auto it : map){
            str.append(it.second,it.first);
        }
        return str;
    }
};
方法3:用一个大小为26的数组来构造
注意数组需要计数，那么当数字大于0的时候就一直输出，直到值为0.
class Solution {
public:
    string customSortString(string S, string T) {
        vector<int>vec(26,0);
        string str;
        for(auto t: T) ++vec[t-'a'];
        for(auto s: S){
            while(vec[s-'a'] > 0){
            str += s;
            --vec[s-'a'];
            }
        }
        for(auto t:T){
            while(vec[t-'a'] > 0){
                str += t;
                --vec[t-'a'];
            }
        }
        return str;
    }
};
方法4:自定义排序方法进行排序
对于字符串T中的任意两个字母a和b，按照其在S中的顺序排序，在S中排前面的在T中也排前面
注意由前到后的顺序排列用"<"
class Solution {
public:
    string customSortString(string S, string T) {
        sort(T.begin(),T.end(),[&](char a, char b){
            return S.find(a) < S.find(b);
        });
        return T;
    }
};