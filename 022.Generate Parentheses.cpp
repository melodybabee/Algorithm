题意：
给定一个数字n，让生成共有n个括号的所有正确的形式
思路：
1.本题应用回溯法（DFS+递归），核心思想是先找到左括号的最大值，开始匹配右括号
2.如果左括号已经封顶，那么退回一个左括号，匹配一个或多个（少于左括号个）右括号，再添加左括号，同时匹配右括号
3.上述为回溯的思想，DFS表示先找到其中某一项最大，再逐渐退回，通过递归实现
注意：
1.回溯进入递归注意首先要写清楚递归结束的条件，即边界条件
2.进入递归之前写清楚判断条件
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        dfs(0,0,"",ret,n);
        return ret;
    }
    
    void dfs(int left, int right, string s, vector<string>&ret,int total){
        if(right == total) ret.push_back(s);
        else{
            if(left < total) dfs(left+1, right, s+"(",ret,total);
            if(right < left) dfs(left, right+1, s+")", ret, total);
        }
    }
};