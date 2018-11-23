题意：
移除括号中最少的无效字符使得其成为一串有效的字符，输出所有情况。
方法1:BFS+queue遍历
思路：
1.建立一个queue先进先出为了把所有等待验证的字符串push进来.
注意题目中求的是移除最少个括号，因此需要一个标记位一旦找到了一个就不再向queue里面push新的元素，后面的字符串会越来越短，因此需要移除的元素会更多。
2.每当取出queue中的一个新元素，检验是否有效，如果有效直接push到结果数组中。
无效的话进入循环，从头部开始依次去掉一个括号再次检验。
此时还需要一个set来记录是否检验过这个字符串，如果检验过跳过，没有检验过把该字符串放到set中，同时push到queue里面。
3.检验字符串是否有效的方法是用一个计数器，遇到左括号+1，遇到右括号-1，再过程中如果出现计数器<0的情况直接返回false
最后检验是否计数器为0，是0返回true，不是0返回false
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string>ret;
        queue<string>q{{s}};
        unordered_set<string>visited;
        bool flag = false;
        while(!q.empty()){
            string temp = q.front();
            q.pop();
            if(isvalid(temp)){
                ret.push_back(temp);
                flag = true;
            }
            if(flag) continue;
            for(int i = 0; i < temp.size(); ++i){
                if(temp[i] != '(' && temp[i] != ')') continue;
                string substr = temp.substr(0,i) + temp.substr(i+1);
                if(!visited.count(substr)){
                    visited.insert(substr);
                    q.push(substr);
                }
            }
        }
        return ret;
    }
                   
    bool isvalid(string s){
        int count = 0;
        for(int i = 0 ; i < s.size(); ++i){
            if(s[i] == '(' )++count;
            if(s[i] == ')') --count;
            if(count < 0) return false;
        }
        if(count != 0) return false;
        else return true;
    }
};
方法2:DFS递归
思路：
1.首先找到左右括号多的个数，注意不是用左括号和右括号做差。
在有左括号的基础上，右括号对它相减，如果左括号不存在那么右括号也为多余的。最后剩下的左右括号为多出来的部分。
2.进入递归如果左右计数器都为0，说明数量上匹配。那么再判断是否有效即可。
3.如果左右不为0，那么开始循环，如果多个左括号或者右括号连在一起，删除一个即可，因为每次只能删除一个，循环多次删除的是同一个，再调用递归。
进入递归后重新判断现在左括号和右括号的数量，判断是否有效。
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        int left = 0;
        int right = 0;
        for(auto a: s){
            if(a == '(') ++left;
            if(a == ')'){
                if(left == 0) ++ right;
                else --left;
            }
        }
        helper(s,0,left,right,res);
        return res;
    }
    
    void helper(string s, int start,int left, int right,vector<string> &res){
        if(left == 0 && right == 0){
            if(isvalid(s)){
                res.push_back(s);
                return;
            }
        }
        for(int i = start; i< s.size(); ++i){
            if(i != start && s[i] == s[i-1]) continue;
            if(left > 0 && s[i] == '(') helper(s.substr(0,i)+s.substr(i+1),i,left -1,right,res);
            if(right > 0 && s[i] == ')') helper(s.substr(0,i)+s.substr(i+1),i,left,right-1,res);
        }
    }
    
    bool isvalid(string s){
        int count = 0;
        for(int i= 0; i < s.size();++i){
            if(s[i] == '(') ++count;
            if(s[i] == ')') --count;
            if(count < 0) return false;
        }
        if(count == 0) return true;
        else return false;
    }
};