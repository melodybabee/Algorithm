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

二刷：
方法1:DFS回溯
注意：
1.注意设置边界条件，所有的corner cases在动手之前考虑
2.遇到排列组合的问题都可以使用DFS+回溯的套路，注意DFS的要点在于先找到满足条件的情况，不断递归找到最深的一点再进行下一个
3.首先设置一个字典对应上键盘上的字母和数字，dfs方程中包括数字，字典，需要返回的数组，遍历到的字母位置，临时记录的字符串
4.临界条件，当遍历到的位置等于数字长度的时候说明已经找到，push_back
5.用一个临时字符串记录下从字典中获得的字符串，注意字符转成数字是-'0'
6.开始循环字符串，计数器+1，在原临时字符串上加入该字符的值，string(1,temp[j])表示加入1个temp[j]字符
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        vector<string>letter{" "," ","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        vector<string>ret;
        dfs(digits, letter,ret,0,"");
        return ret;
    }
    
    void dfs(string digits, vector<string>&letter, vector<string>&ret, int count, string s){
        if(count == digits.size()){
            ret.push_back(s);
            return;
        }
        string temp = letter[digits[count]-'0'];
        for(int j = 0; j < temp.size(); ++j){
            dfs(digits,letter,ret,count+1,s + string(1,temp[j]));
        }
    }
};

方法2：迭代
思路：
1.同样使用DFS，与回溯不同的是，需要在for循环内部再建一个临时数组，用来存放每次更新后的新值，在更新之后把ret换为临时的数组
2.注意在最内层循环的时候，需要遍历的是ret中已有的字符串，在此基础之上加上新的值
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        vector<string>letter{" "," ","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        vector<string>ret{""};
        for(int i = 0; i < digits.size(); ++i){
            string temp = letter[digits[i]-'0'];
            vector<string> st;
            for(int j = 0; j < temp.size(); ++j){
                for(auto s:ret) st.push_back(s+string(1,temp[j]));
            }
            ret = st;
        }
        return ret;
    }
};