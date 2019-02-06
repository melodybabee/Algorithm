题意：根据给出的四则运算，计算出加上所有种类括号后的结果
【重点复习】思路：
1.分治法的典型题目，因为括号的作用就是先进行计算，那么从头部开始遍历，遇到符号之后开始进入递归
即在括号的左右两侧加上括号，分别记录下左右两侧的值
2.左右的数组计算下当前左边半侧和右边半侧的值，如果没有符号且数组为空的话，那么将字符转换为数字直接输入数组
3.再根据递归前的符号进行计算，输入当前遍历到的位置的新的数组中。
注意：
1.因为一个字符串会有多种不同的计算方法，所以在数组中会有若干的计算后的结果
比如 2*3-4*5 当遍历到*的时候对2*3-4进行遍历，就会有2*-1，6-4两种情况，数组汇总有-2和2两个数字
要依次进行遍历计算
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int>vec;
        for(int i = 0; i < input.size(); ++i){
            if(input[i] == '+' || input[i] == '-' || input[i] == '*'){
                vector<int> left = diffWaysToCompute(input.substr(0,i));
                vector<int> right = diffWaysToCompute(input.substr(i+1));
                for(int j = 0; j < left.size(); ++j){
                    for(int k = 0; k < right.size(); ++k){
                        if(input[i] == '+') vec.push_back(left[j] + right[k]);
                        else if(input[i] == '-') vec.push_back(left[j] - right[k]);
                        else if(input[i] == '*') vec.push_back(left[j] * right[k]);
                    }
                }
            }
        }
        if(vec.empty()) vec.push_back(stoi(input));
        return vec;
    }
};
优化：DP
上面的方法有大量重复计算的步骤，那么存入一个map中，可降低时间复杂度。
思路：
1.在map中记录下每个字符串对应的可能数值，作为数组的形式存在map的value中
如果能在map中找到，直接返回；如果不能找到，那么在map中插入新的值
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        unordered_map<string,vector<int>> m;
        return computewithdp(input,m);
    }
    
    vector<int> computewithdp(string input, unordered_map<string,vector<int>> &map){
        vector<int>res;
        for(int i = 0; i < input.size(); ++i){
            if(input[i] == '+' || input[i] == '-' || input[i] == '*'){
                string s1 = input.substr(0,i);
                vector<int> v1;
                vector<int> v2;
                if(map.count(s1)){
                    v1 = map[s1];
                }else{
                    v1 = computewithdp(s1,map);
                }
                string s2 = input.substr(i+1);
                if(map.count(s2)){
                    v2 = map[s2];
                }else{
                    v2 = computewithdp(s2,map);
                }
                for(auto v : v1){
                    for(auto u : v2){
                        if(input[i] == '+'){
                            res.push_back(u + v);
                        }else if(input[i] == '-'){
                            res.push_back(v - u);
                        }else{
                            res.push_back(v * u);
                        }
                    }
                }
            }
        }
        
        if(res.empty()) res.push_back(stoi(input));
        map[input] = res;
        return res;
    }
};