题意：找到没有重复元素的最长子串，最多改变k个元素
思路：
1.同样应用滑动窗口。定义左指针为起点，用右指针一次循环字符串，边循环边记录每个字符的数量。
用一个值记录下来出现过的字符的较大值。注意这个值是不断增大的。
2.因为最多只能改变k次，那么尽量少的进行改变，结果就是现在的字符长度减去出现过的最多次数的字符数量，表示需要改变的字母。
如果这个值的大小要比k还要大，那么说明需要移动左指针了。
3.注意滑动窗口维护的就是最长的长度，不一定满足条件的长度是满足条件的结果。可以用ABAABBBB举个例子来判断。
但是第一次更新res结果的时候，一定是满足条件的值。
4.移动左指针之后需要在map中更新value,但是所能遇到的最大的字符数量只会递增不会减少。
注意：
用（26，0）数组的时候需要把字符转换为数字，因为都是大写字母，因此要-'A'
class Solution {
public:
    int characterReplacement(string s, int k) {
        int res = 0;
        int start = 0;
        int count = 0;
        vector<int> vec(26,0);
        for(int i = 0; i < s.size(); ++i){
            ++vec[s[i]-'A'];
            count = max(count, vec[s[i]-'A']);
            while((i-start+1-count) > k){
                --vec[s[start]-'A'];
                ++start;
            }
            res = max(res, i - start +1);
        }
        return res;
    }
};

string stringToString(string input) {
    assert(input.length() >= 2);
    string result;
    for (int i = 1; i < input.length() -1; i++) {
        char currentChar = input[i];
        if (input[i] == '\\') {
            char nextChar = input[i+1];
            switch (nextChar) {
                case '\"': result.push_back('\"'); break;
                case '/' : result.push_back('/'); break;
                case '\\': result.push_back('\\'); break;
                case 'b' : result.push_back('\b'); break;
                case 'f' : result.push_back('\f'); break;
                case 'r' : result.push_back('\r'); break;
                case 'n' : result.push_back('\n'); break;
                case 't' : result.push_back('\t'); break;
                default: break;
            }
            i++;
        } else {
          result.push_back(currentChar);
        }
    }
    return result;
}

int stringToInteger(string input) {
    return stoi(input);
}

//main函数
int main() {
    string line;
    //读取输入值，只要有输入值
    while (getline(cin, line)) {
        string s = stringToString(line);
        getline(cin, line);
        int k = stringToInteger(line);
        
        //调用Solition类里面的characterReplacement方法
        int ret = Solution().characterReplacement(s, k);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}