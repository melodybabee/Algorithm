题意：
分割一个string，如果分割后的结果都是回文的，则输出所有切割好的数组。
思路：
1.需要两个vector,从第一个字符开始切割，如果是回文的，把第一个字符push到小的vector中，再递归后面的长字符串。
长字符串会再次进入dfs方法，从第一个字符开始切割。
如果切割到最后头结点的位置与字符串的长度相等，则把该小vector，push到大的vector中，再按照push的顺序依次释放小vector。
如果切割过程中发现不是回文的，则将小vector中的上一段pop_back()
2.不断进行回溯和递归，直到头结点循环到等于s.size()的时候输出
3.需要再构建一个函数来判断是否是回文数字
举例abcd的输出顺序：
a,b,c,d,cd,bc,bcd,ab,abc,abcd
举例aabc的输出顺序：
a,a,b,c,bc,ab,abc,aa,b,c,bc,aab,aabc
因为aa是回文串，所以剩下的b,c需要当作新串来处理
注意：
1，本题用到了回溯的思想，回溯的思想的最佳实例是走迷宫，需要反复练习
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<string> str;
        vector<vector<string>> ret;
        dfs(s,0,str,ret);
        return ret;
    }
    void dfs(string s, int start, vector<string>&str, vector<vector<string>> &ret){
        if(start == s.size()){
            ret.push_back(str);
            return;
        }
        for(int i = start; i< s.size();++i){
            if(isPalindrome(s,start,i)){
                str.push_back(s.substr(start,i-start+1));
                dfs(s,i+1,str,ret);
                str.pop_back();
            }
        }
    }
    bool isPalindrome(string s, int start, int end){
        while(start < end){
            if(s[start] != s[end]) return false;
            ++start;
            --end;
        }
        return true;
    }
    
    
};