题意：给字符串添加加减乘使得总值等于目标值。
思路：
1.因为涉及逐位判断，那么所用的方法就是DFS递归。
2.当数值到了最后一位且总和等于目标值的时候，push进入数组。
3.进入递归之后，从当前位置开始进行循环，因为字符可以拆分成一位一位的，也可以拆分成若干位连接。
所以用一个cur记录下切分的位置，前半部分是cur,后半部分是next.
如果cur的长度大于2，而且第一位为0，那么直接返回，这种情况需要舍弃，后面再进行切割也无法切割出有效的值。
4.如果结果字符串为空的话，直接用第一位进行调用。
注意一共有4个变量值，返回的引用类型的结果数组，返回的字符串，求和的结果值，和一个目前需要改变的值作为乘法时使用。
5.不为空分别调用+，-，*三种情况。
如果是加法，返回字符串用当前值+新的值，求和结果用当前值+新的值，改变元素是正的cur
如果是减法，返回字符串用当前值-新的值，求和结果用当前值-新的值，改变元素是负的cur
如果是乘法，返回字符串用当前值+新的值，求和结果是（当前结果-之前要改变的值）+（要改变的值*当前值），改变元素是要改变的值*当前值
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string>ret;
        dfs(num,target,0,0,"",ret);
        return ret;
    }
    
    void dfs(string num, int target,long long diff,long long curnum, string curret,vector<string>&ret){
        if(num.size() == 0 && curnum == target){
            ret.push_back(curret);
        }
        
        for(int i = 1; i <= num.size();++i){
            string cur = num.substr(0,i);
            if(cur.size() >= 2 && cur[0] == '0') return;
            string next = num.substr(i);
            if(!curret.empty()){
                dfs(next,target,stoll(cur),curnum + stoll(cur),curret + '+' + cur,ret);
                dfs(next,target,-stoll(cur),curnum -stoll(cur),curret + '-' + cur,ret);
                dfs(next,target,diff *stoll(cur),diff*stoll(cur)+curnum - diff,curret + '*' + cur,ret);
            }else{
                dfs(next,target,stoll(cur),stoll(cur),cur,ret);
            }
            
        }
    }
};