concatenation 串联 
intervening 介于中间的
题意：
找到string中包含的所有单词串联起来，所有满足条件的第一个位置，每个单词的长度相同，可能会有重复的单词
思路：
1.首先遍历vector，把vector的单词存到一个散列表中
这一步可以用for循环写：
for(int i = 0; i< words.size(); ++i){
                ++map1[words[i]];
        }
如果想简单一点可以用auto:
for (auto &a : words) ++m1[a];
	for(auto i : vec){
		cout << i << endl;
	}
和
	for(auto &i : vec){
		cout << i << endl;
	}
}
在此处没有区别，都是指vec中的单词元素
2.同时开始遍历string,i表示每次遍历的起始位置，j表示第几个单词的位置,j每次增加一个单词的长度，用于表示string的连续性
3.如果在map1中没有找到遍历的单词，那么break;
如果找到了，在map2中为这个单词加1，如果该单词的数值大于map中的，那么同样break
4.当j遍历到vector的长度而还没有break,说明map2与map1中的单词完全匹配，那么返回此时i的位置
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        if(s.empty() || words.empty()) return ret;
        unordered_map<string,int> map1;
        int length = words[0].size();
        for(int i = 0; i< words.size(); ++i){
                ++map1[words[i]];
                //cout << map1[words[i]] << endl;
        }
        for(int i = 0; i < s.size();++i){
            int j = 0;
            unordered_map<string,int> map2;
            for(j = 0; j < s.size(); ++j){
                if(map1.find(s.substr(i+j*length,length)) == map1.end()) break;
                ++map2[s.substr(i+j*length,length)];
                if(map2[s.substr(i+j*length,length)] > map1[s.substr(i+j*length,length)]) break;
            }
            if(j==words.size()) ret.push_back(i);
            
        }
        return ret;
    }
};

优化【需要复习】：
T(n) = O(n);
思路：
1.简化时间复杂度，不需要在筛选string的时候用两个for循环
2.同样需要首先把所有单词存在一个hashmap中，用i进行for循环的遍历
注意i的范围在第一个单词的长度内即可，因为后面的for循环会依照单词来进行判断
也就是遍历的顺序为0，3，6，8，12，15，接着是1，4，7，9，13，16，最后是2，5，8，10，14，17这样便可以遍历到所有字符
3.设立一个left作为左边界，count为匹配上的单词个数，用j来作为查找单词的指针，每次增加一个单词的长度
如果该单词在map1中没有，清空map2。left移动一个单词的长度。
如果存在，在map2中放入这个单词。
如果map2单词的个数小于等于map1，那么说明匹配上一个单词，count+1;
如果map2单词的个数大于map1，获取目前left指针所在的位置的单词，在map2中对这个单词-1，如果此时m2[t1]<m1[t1]了，说明一个匹配没了，那么对应的count也要-1
	比如：s = barfoofoo, words = {bar, foo, abc}, 我们给words中新加了一个abc，目的是为了遍历到barfoo不会停止，那么当遍历到第二foo的时候, m2[foo]=2, 而此时m1[foo]=1
	那么就取出左边界的单词，数量-1，为了判断是否是s = barbar,words = {bar}的情况
	如果相等，则匹配，如果map2中的数量小于map1,则说明不匹配，第一个单词left指针右移
当匹配的数量count和单词个数相等时，在vector中push进去当前的left的位置。因为单词的顺序可以任意，因此此时去除第一个单词的位置，count -1，左边界右移继续匹配
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(s.empty() || words.empty()) return {};
        vector<int> ret;
        int length = words[0].size();
        int cnt = words.size();
        int n = s.size();
        unordered_map<string,int> map1;
        for(auto &sub: words) ++map1[sub];
        for(int i = 0; i < length; ++i){
            int left = i;
            int count = 0;
            unordered_map<string, int> map2;
            for(int j = i; j <= n - length; j += length){
                string str = s.substr(j, length);
                if(map1.count(str)){
                    ++map2[str];
                    if(map2[str] <= map1[str]){
                        ++count;
                    }else{
                        while(map2[str] > map1[str]){
                            string st = s.substr(left, length);
                            --map2[st];
                            if(map2[st] < map1[st]){
                                --count;
                            }
                            left += length;
                        }
                    }
                    if(count == cnt){
                        ret.push_back(left);
                        --map2[s.substr(left,length)];
                        --count;
                        left += length;
                    }
                }else{
                    map2.clear();
                    count = 0;
                    left = j + length;
                }
            }
        }
        return ret;
                                 
    }
};