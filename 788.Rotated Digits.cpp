题意：把数字旋转180，如果不是相同的数字那么+1。求最后有几位不相同的数字。
方法一：暴力求解
思路：
1.因为判断从1到N的范围内的结果，因此对每一个数字进行检查即可
2.分析题意得知，如果在数字中有3，4，7那么一定不满足情况；0，1，8不能单独存在，也就是说2，5，6，9其中之一必须存在
3.那么对于每一个数字，设置一个flag,如果3,4,7存在直接返回false;只有当2,5,6,9存在的时候flag才是true
最后返回flag
注意：
1.把数字转换为字符串的形式便于进行一位一位的判断，用to_string直接转即可。
class Solution {
public:
    int rotatedDigits(int N) {
        int ans = 0;
        for(int i= 1; i <= N; ++i){
            if(check(i)) ++ans;
        }
        return ans;
    }
    bool check(int num){
        string s = to_string(num);
        bool flag = false;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == '3' || s[i] == '7' || s[i] == '4') return false;
            if(s[i] == '2' || s[i] == '5' || s[i] == '6' || s[i] == '9') flag = true;
        }
        return flag;
    }
};
方法2:DP
思路：
1.从头部开始循环每个数字,dp[i]用来记录数字的状态，0是无效，1是不可单独存在，2是有效
2.当小于0的时候初始化DP数组，遇到2的时候结果计数器+1
3.当大于10之后，一位用来记录商，一位用来记录余数，如果都是1，更新为1，在这个基础之上如果都大于等于1，那么更新为2
4.最后返回结果计数器的值
class Solution {
public:
    int rotatedDigits(int N) {
        vector<int>dp(N+1);
        int ans = 0;
        for(int i = 0; i <= N ;++i){
            if(i <  10){
                if(i == 0 || i == 1 || i == 8) dp[i] = 1;
                if(i == 2 || i == 5 || i == 6 || i == 9){
                    dp[i] = 2;
                    ++ans;
                }
            }else{
                int p = dp[i%10];
                int q = dp[i/10];
                if(p == 1 && q == 1) dp[i] = 1;
                else if(p >= 1 && q >= 1){
                    dp[i] = 2;
                    ++ans;
                }
            }
        }
        return ans;
    }
};