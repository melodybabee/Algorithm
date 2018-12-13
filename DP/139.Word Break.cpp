题意：
是否可以将字符串拆分为字典中的子串。
方法1:暴力拆解
T(n) = O(n^n),TLE
思路：
1.首先将字典中的数组放在hashset中便于线性查找
2.开始进入递归，如果第一个指针的位置等于字符串的长度，说明已经匹配到末尾，那么直接返回true
3.从头部开始循环从1开始的子串长度，如果在字典中找到前半部分，那么把后半部分进入递归，依次实现拆解。
如果循环到字符串结束仍然没有匹配上，返回false。
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordset(wordDict.begin(),wordDict.end());
        return helper(s,wordset,0);
    }
    bool helper(string s, unordered_set<string>&wordset,int start){
        if(start == s.size())  return true;
        for(int i = start +1; i <= s.size();++i){
            if(wordset.count(s.substr(start,i-start)) && helper(s,wordset,i)){
                return true;
            }
        }
        return false;
    }
};
方法2：记忆化递归
T(n) = O(n^2); S(n) = O(n);
思路：
1.在暴力拆解的基础上进行优化。
2.递归是自上向下解决问题，每次都需要重复的计算子问题，那么如果把每个子问题的结果自下向上记录下来，那么后面的递归就不再需要重新计算，大大提高了时间复杂度。
3.mem[i]表示从0-i的范围是否可以拆分，初始值为-1。
每当循环到后面的位置前面已经匹配上之后，可以拆分值为1，返回true;不可拆分为0,返回false.
4.每次重新递归更新记忆数组，但是记忆数组有可能不会被完全更新。
举例：
比如
"catsandog"
["cats", "dog", "sand", "and", "cat"]是不能匹配的
在内部for循环之前输出，他的记忆数组更新后是：
不满足情况输出原数组：
-1-1-1-1-1-1-1-1-1-1
把不满足情况的当次的start8位置更改为0:
-1-1-1-1-1-1-1-1 0-1
递归回到调用8的位置的方法，本次的start也会更改为0：
-1-1-1 0-1-1-1-1 0-1
重新进入for循环，循环cats,但是第8位已经被标记为-1，因此不能在此之前进入循环，故也为-1。
-1-1-1 0 0-1-1-1 0-1
后直接返回false;
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordset(wordDict.begin(),wordDict.end());
        vector<int>mem(s.size(),-1);
        return helper(s,wordset,mem,0);
    }
    bool helper(string s, unordered_set<string>&wordset,vector<int>&mem,int start){
        if(start == s.size())  return true; 
        if(mem[start] != -1) return mem[start];
        for(int i = start +1; i <= s.size();++i){
            if(wordset.count(s.substr(start,i-start)) && helper(s,wordset,mem,i)){
                mem[start] = 1;
                return true;
            }
        }
        mem[start] = 0;
        return false;
    }
};
方法3，DP
T(n) = O(n^2); S(n) = O(n);
思路：
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> word (wordDict.begin(),wordDict.end());
        vector<bool>dp(s.size()+1,false);
        dp[0] = true;
        for(int i = 0; i < dp.size();++i){
            for(int j = 0; j < i; ++j){
                if(dp[j] && word.count(s.substr(j,i-j))){
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
};
方法4:BFS
思路：
1.总体思路和记忆化递归一样，记忆化递归是把原先的状态入栈，BFS是把他放到队列中。
2.用visited数组对之前遍历过的元素进行存储，作用和mem数组相同，队列中取出一个位置进行遍历，把可以拆分的新位置存入队列中，遍历完成后标记当前位置，然后再到队列中去取即可
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> word(wordDict.begin(),wordDict.end());
        vector<bool>visited(s.size());
        queue<int>q{{0}};
        while(!q.empty()){
            int start = q.front();
            q.pop();
            if(!visited[start]){
                for(int i = start+1; i <= s.size();++i){
                    if(word.count(s.substr(start,i-start))){
                        q.push(i);
                        if(i == s.size()) return true;
                    }
                }
                visited[start] = true;
            }
        }
        return false;
    }
};

12.11复习：
DP：
注意：
1.因为DP需要初始化，因此DP的长度会比字符串的长度大一位，每次在DP数组中更新的时候更新的是比字符串大一位的true或者false
2.因此在找子串的时候其实i已经在循环到的后一位上了，那么长度直接就是i-j,dp[i]表示的是以i为结尾的字符串是否能在set中匹配
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>set(wordDict.begin(),wordDict.end());
        vector<bool>dp(s.size()+1,false);
        dp[0] = true;
        for(int i = 0; i < dp.size(); ++i){
            for(int j = 0;j < i;++j){
                if(dp[j] && set.count(s.substr(j,i-j))){
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
};
BFS注意：
1.核心思想是从栈顶元素开始，一位一位查找，如果找到了，把坐标push进栈。如果坐标等于字符串长度那么返回true
需要设置一个数组判断该位是否被查找过
2.注意i从第一位开始到字符串长度那一位，i表示的是长度，start从0开始和字符串相同
3.因此计算子串的时候直接是s.substr(start,i-start)
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>set(wordDict.begin(),wordDict.end());
        queue<int>q;
        vector<bool>visited(s.size());
        q.push(0);
        while(!q.empty()){
            int start= q.front();
            q.pop();
            if(!visited[start]){
                for(int i = start+1; i <= s.size();++i){
                    if(set.count(s.substr(start,i-start))){
                        q.push(i);
                        if(i == s.size()) return true;
                    }
                }
                visited[start] = true;
            }
        }
        return false;
    }
};
