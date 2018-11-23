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

二刷：
距离第一次刷一个月出头，完全想不出来思路，这种看讨论区得到最优解的思路确实不是一上来就能想到的，唯有重复重复重复！
注意：
1.思路卡顿在没有动手写之前纠结于这道题难道需要分别判断左括号和右括号的次数吗？接着就不敢往下想
事实证明就是要这样。这种思想已经出现多次，自以为很麻烦需要写的东西很多，一这是正确思路的必经之路，二事实上写出来了也并不麻烦，要大胆继续想
2.最优解的巧妙性在于先对左括号进行DFS，再在此基础之上对右括号进行DFS，括号问题核心是【先左后右】
3.在进行递归的时候string类型的一个字符要用"",不能写作''
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> str;
        dfs(0,0,n,str,"");
        return str;
    }
    void dfs(int left, int right, int total,vector<string>&str, string s){
        if(right == total) str.push_back(s);
        if(left < total) dfs(left +1, right,total, str,s+"(");
        if(right < left) dfs(left,right +1, total, str, s+ ")");
    }
    
};