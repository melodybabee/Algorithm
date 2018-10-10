题意：
输入一串数字，数字对应电话键盘上面的字母，排列组合输出所有可能的组合
思路：
1.首先建立一个vector存入键盘上对应的所有子串，注意因为0，1不对应，因此设置为空
2.用for循环来遍历digits,注意将string转换为int
3.如果数字不符合要求，break，根据数组找出vector中对应的字符串
4.建立一个temp数组，用两个for来循环结果数组和字符串中的字母，多对多对应，push到临时数组中
5.再将临时数组和结果数组交换，为了更新结果数组
6.最后输出结果数组
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ret = {};
        if(digits.empty()) return ret;
        vector<string> nums = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        ret.push_back("");
        for(int i = 0; i < digits.size(); ++i){
            int num = digits[i]-'0';
            if(num < 0 || num > 9) break;
            string letter = nums[num];
            if(letter.empty()) continue;
            vector<string> temp;
            for(int p = 0; p<ret.size();++p){
                for(int q = 0; q<letter.size();++q){
                    temp.push_back(ret[p]+letter[q]);
                }
            }
            ret.swap(temp);
        }
        return ret;
    }
};

【学习DFS和回溯写法】