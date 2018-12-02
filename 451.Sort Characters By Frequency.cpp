题意：
根据字符出现的频次排序字符串。
方法一：优先队列heap
思路：
1.首先用一个哈希表来记录字符出现的次数,key对应字符,value对应出现的次数
2.再把map中的数组以pair的形式存放到优先队列中，注意因为优先队列中的元素按照key排序，因此先放value再放key.
3.最后当queue不为空的时候，输出栈顶元素，在返回的结果中输出value个key元素
注意：
1.push方法，因为push的是pair形式的数字，因此在每一对之前都需要用{},其他关于优先队列的操作和queue一样
2.append()
直接添加另一个完整的字符串:str1.append(str2);
添加另一个字符串的某一段子串:str1.append(str2, 11, 7);str2中添加第11位开始的7个字符
添加几个相同的字符:str1.append(5, '.');
3.priority_queue的pair顺序要根据key排序
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char,int>map;
        priority_queue<pair<int,char>>queue;
        string ret = "";
        for(auto a: s){
            ++map[a];
        }
        for(auto it :map){
            queue.push({it.second,it.first});
        }
        while(!queue.empty()){
            auto q = queue.top();
            queue.pop();
            ret.append(q.first,q.second);
        }
        return ret;
    }
};
方法二：sort方法复写
思路：
1.首先把字符放在哈希表中
2.对字符进行排序，复写排序方法，先按照在map中的value排序，如果相等按照字母表顺序排序
注意：
1.复写方法的时候[]里面的&表示对map的引用，表示使用外部变量，不然在sort方法中无法识别map
char&a和char&b和s.begin()的类型统一。
C++ STL sort: http://www.cppblog.com/mzty/archive/2005/12/15/1770.html
2.同时注意处理频率相等的情况，不然会频率相等的情况会穿插输出
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char,int>map;
        for(auto a:s) ++map[a];
        sort(s.begin(),s.end(),[&](char&a,char&b){
             return map[a] > map[b] ||(map[a] == map[b] && a >b);
        });
        return s;
    }
};
方法3:建立字符串数组
思路：
1.建立一个数组，数组中的位置就是某个字符在string中出现的次数。
2.注意从map中向vector中添加字符的时候，坐标表示位数，值是string类型的，所以还需要append(频数,字符)的形式，方便后面输出。
3.从后向前遍历数组，如果为空跳过，不为空的时候在已有的结果后面添加上该位置的字符串。
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char,int>map;
        vector<string>vec(s.size()+1,"");
        string str = "";
        for(auto a: s) ++map[a];
        for(auto it :map){
            vec[it.second].append(it.second,it.first);
        }
        for(int i = vec.size()-1; i >= 0; --i){
            if(vec[i] != "") str.append(vec[i]);
        }
        return str;
    }
};
