题意：从指定机场开始重新安排行程单
方法一：DFS
思路：
1.因为需要输出一条路径，而题目中说了一定存在这条路径，因此DFS是最直接的方法
2.首先构建图，因为相同的选择下需要按照字典序排列，所以利用multiset自动进行排序
3.从JFK开始进入DFS，只要当它对应的value不为空的时候就从起点开始遍历它的value值，每次遍历道一位删除掉当前的位置
对遍历到的字符串重新进入递归，如果没有对应的那么在数组中输入结果
3.因为DFS会自一个输出最后的结果，所以最终的结果还需要对数组进行反向
注意：
1.本题中默认了一定会有结果，所以不存在不满足条件的情况
2.注意while循环从value的起点位置开始，因为迭代器begin()是指针类型，因此需要取值符号*
但是删除部分erase()删除的也是指针类型，因此不需要取值号
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        unordered_map<string,multiset<string>>map;
        vector<string>ans;
        for(auto t : tickets){
            map[t.first].insert(t.second);
        }
        dfs(map,ans,"JFK");
        reverse(ans.begin(),ans.end());
        return ans;
    }
    
    void dfs(unordered_map<string,multiset<string>>&map, vector<string>&ans,string cur){
        while(map[cur].size()){
            string s = *map[cur].begin();
            map[cur].erase(map[cur].begin());
            dfs(map,ans,s);
        }
        ans.push_back(cur);
    }
};
补充：set与multiset
1.set的含义是集合，它是一个有序的容器，里面的元素都是排序好的，支持插入，删除，查找等操作，就像一个集合一样。
因为建立在红黑树的基础上，以一个BST，因此所有的操作的都是严格在logn时间之内完成，效率非常高。
2.set和multiset的区别是：set插入的元素不能相同，但是multiset可以相同。multiset可以按照ASCII码的顺序进行排列
【原理待学习】
方法2:迭代
思路：
1.建图的过程和DFS完全相同，但是在输出的过程中，输出的条件是如果map中对应的value为空，那么在结果中插入新的值。
2.如果不为空，那么把第一个位置的值输入栈中。
由于满足后进先出的规律，因此用stack最合适，同时每次插入需要从第一位上开始，最后直接返回
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        unordered_map<string,multiset<string>>map;
        vector<string>ans;
        stack<string>st{{"JFK"}};
        for(auto t : tickets){
            map[t.first].insert(t.second);
        }
        while(!st.empty()){
            string temp = st.top();
            if(map[temp].empty()){
                ans.insert(ans.begin(),temp);
                st.pop();
            }else{
                st.push(*map[temp].begin());
                map[temp].erase(map[temp].begin());
            }
        }
        return ans;
    }
    
};
