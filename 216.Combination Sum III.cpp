题意：
给定一个目标值，输出限定个数内1-9中所有和等于目标值的组合。
思路：
1.利用DFS+回溯的方法，边界条件判断目标值-当前值，如果小于0，说明不满足题意，直接return
2.如果等于0，说明找到一种情况，那么直接push到输出的大数组中
3.从1-9开始依次push到内部小数组中，进入递归加上下一位，总和减去当前位。递归结束再依次从尾部pop出来
注意：
1.在递归中需要一个参数i用来使所有的输出值不重复，每次从当前位的下一位开始进入递归循环
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>>ret;
        vector<int> temp;
        helper(ret,temp,k,1,n);
        return ret;
    }
    void helper(vector<vector<int>>&ret,vector<int>&temp,int k, int num, int n){
        if(n < 0) return;
        if(n == 0 && temp.size() ==k) ret.push_back(temp);
        for(int i = num; i <=9 ;++i){
            temp.push_back(i);
            helper(ret,temp,k,i+1,n-i);
            temp.pop_back();
        }
    }
};