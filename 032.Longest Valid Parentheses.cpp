题意：
找到最长的有效括号
法一：利用stack
T(n) = O(n); S(n) = O(n);
思路：
1.从左到右扫描，遇到左括号进栈，遇到右括号的时，如果栈为空，把start指针移动到i后一位
2.如果栈不空，返回栈顶元素。如果此时栈空，那么返回值是此时的i-start+1，如果栈仍不空，那么还有左括号剩余，返回此时的i减去当前的栈顶元素
class Solution {
public:
    int longestValidParentheses(string s) {
        int start = 0;
        int ret = 0;
        stack<int> st;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] =='(') st.push(i);
            else{
                if(st.empty()) start = i+1;
                else{
                    st.pop();
                    ret = st.empty() ? max(ret,i-start+1) : max(ret,i-st.top());
                }
            }
        }
        return ret;
    }
};
法二：DP
T(n) = O(n); S(n) = O(n);
思路：
1.用一个dp[]来存储遍历到每个字符时累积的长度。遇到右括号的时候更新，如果当前位的前一位减去前一位的累积值的位置是左括号，当前位+2，说明匹配上一对
2.同时当前位需要加上之前累积的值，返回当前位与之前的和中较大的一个
class Solution {
public:
    int longestValidParentheses(string s) {
        int ret = 0;
        vector<int> dp(s.size(),0);
        for(int i = 1; i < s.size();++i){
            if(s[i] == ')'){
                if(s[i-1-dp[i-1]] == '(') dp[i] = dp[i-1]+2;
                dp[i] += dp[i-dp[i]];
            }
            ret = max(ret,dp[i]);
        }
        return ret;
    }
};
法三：思路与上述类似，但是不用额外的空间
T(n) = O(n); S(n) = O(1);
思路：
1.从头开始遍历，遇到左右括号分别计数相加，如果左右相等，那么返回之前最大值和当前右括号数量2倍中的较大值
如果右括号的数量大于左括号，那么左右同时置0
2.从尾部开始遍历，遇到左右括号分别计数相加，如果左右相等，那么返回之前最大值和当前左括号数量2倍中的较大值
如果左括号的数量大于右括号，那么左右同时置0
3.最后返回较大值