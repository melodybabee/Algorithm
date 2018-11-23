题意：
所有单词都需要在字典中，一次可以更改一个字母，问从起始字母到结束字母最少需要多少次。
方法一：BFS
思路：
1.题目中的含义是找到最短的次数可以从一个单词变成另一个单词。
这个问题放在平时操作应该是一个一个尝试，如果尝试到了在字典中的单词，那么开始循环下一个。
但是如果尝试到了一个是在原基础上继续循环还是换一个字母重新开始循环，就是BFS和DFS的区别。
而找最短路径通常运用的是BFS的方法，BFS相当于在一个中心范围内的小圈中一层一层慢慢扩大，DFS相当于一条路走到黑，不一定是最短的距离。
2.用到BFS通常需要queue来依次push进去需要push的元素，再依次取出。
3.本道题中首先运用一个set把字典中的单词一次放入set便于线性查找。
4.用一个hashtable来记录每个单词对应的系数，为了放回最后所求的长度。
5.queue中放入begin单词，开始从第一个位置循环，替换，此处注意需要用一个临时复制的单词来替换并判断，使原单词能不断被替换。
替换单词设置一个字符，从a开始循环到z即可。
6.如果字典中共有而且等于尾部单词，那么返回这个饭次对应的系数；如果字典中共有但是不等于尾部元素，那么放到queue中开始下一次判断。
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> word(wordList.begin(),wordList.end());
        unordered_map<string,int> map;
        map[beginWord] = 1;
        queue<string>q{{beginWord}};
        while(!q.empty()){
            string temp = q.front();
            q.pop();
            for(int i = 0 ;i < temp.size();++i){
                string newword = temp;
                for(char ch = 'a'; ch <= 'z';++ch){
                    newword[i] = ch;
                    if(newword == endWord && word.count(newword)) return map[temp] +1;
                    if(word.count(newword) && !map.count(newword)){
                        q.push(newword);
                        map[newword] = map[temp]+1;
                    }
                }
            }
        }
        return 0;
    }
};
优化：删减hashtable对应的单词系数，换做循环
思路：
1.设置一个循环，每当queue开始新的一层循环的时候，计数器+1
因此需要在while循环内部加一层for循环，遍历本次queue的长度，遍历结束后计数器+1
2.这样把新在字典中找到的单词也push到queue中，进入queue判断是否和尾部单词相等，相等直接输出
3.把字典中的单词push到queue之后要删除字典中的该单词，不然会形成环，无解
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> word(wordList.begin(),wordList.end());
        queue<string>q{{beginWord}};
        int count = 0;
        while(!q.empty()){
            for(int k = q.size(); k > 0 ;--k){
            string temp = q.front();
            q.pop();
            if(temp == endWord) return count+1;
            for(int i = 0 ;i < temp.size();++i){
                string newword = temp;
                for(char ch = 'a'; ch <= 'z';++ch){
                    newword[i] = ch;
                    if(word.count(newword) && newword != temp){
                        q.push(newword);
                        word.erase(newword);
                        }
                    }
                }
            }
            ++count;
        }
        return 0;
    }
};