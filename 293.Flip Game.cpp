题意：把字符串中两个连续的++更改为--，输出所有情况
思路：
1.设置一个返回数组，从第一位开始遍历字符串，如果连续两位都是+，那么更改为-
2.因为每次需要返回一个新的字符，所以进入遍历的时候需要先复制一下之前的字符串
class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        vector<string>vec;
        if(s.size() < 1) return vec;
        for(int i = 0 ; i < s.size()-1; ++i){
            string temp = s;
            if(temp[i] == '+' && temp[i+1] == '+'){
                temp[i] = '-';
                temp[i+1] = '-';
                vec.push_back(temp);
            }
        }
        return vec;
    }
};