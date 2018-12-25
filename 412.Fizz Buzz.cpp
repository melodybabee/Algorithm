题意：对于不同的数字输出不同的数字或者规定的单词。
思路：
1.先判断能同时整除3和5的情况，返回；
2.在分别判断能整除3或者5的情况，返回；
3.最后返回一般情况，注意所有的情况都需要else,不能只写作if
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string>ret;
        for(int i = 1; i <= n ; ++i){
            if(i % 3 == 0 && i % 5 == 0 )ret.push_back("FizzBuzz");
            else if(i % 3 == 0) ret.push_back("Fizz");
            else if(i % 5 == 0) ret.push_back("Buzz");
            else ret.push_back(to_string(i));
        }
        return ret;
    }
};