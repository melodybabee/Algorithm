题意：
找到从1到N的所有K位组合数。
法一：回溯+递归
思路：
1.涉及枚举的题目应该首先想到回溯+递归。因为本题是找所有的组合数，那么先从第一个开始找，再找第二个，依次类推。
2.一旦满足了位数的要求，那么退回最后一个数字，进行下一位的循环。
3.临界条件是当子数组的位数与K相等的时候，就push到大的数组当中去。
注意：
1.因为所有数字的第一位是从1开始，所以进入dfs函数的时候初始值要为1。
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> temp;
        vector<vector<int>> ret;
        dfs(1,n,k,temp,ret);
        return ret;
    }

    void dfs(int start,int n,int k,vector<int>&temp,vector<vector<int>>&ret){
        if(temp.size()==k) return ret.push_back(temp);
        for(int i = start; i <= n; ++i){
            temp.push_back(i);
            dfs(i+1,n,k,temp,ret);
            temp.pop_back();
        }
    }
};
法二：遍历
思路：
1.用i来表示位数，因此当i==k-1的时候就可以把ret push_back到temp中
2.temp[i]表示当前位置上的值，如果当前值大于n,那么位数减1
3.如果都不满足，i移动到下一位，使下一位的值等于当前位的值，再进入循环的时候把下一位+1，因为相同的数字不能存在
4.最后i会从最高位开始后退，退到小于0的时候返回ret,结束循环。
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ret;
        vector<int> temp(k,0);
        int i = 0;
        while(i >= 0){
            ++temp[i];
            if(temp[i] > n) --i;
            else if(i == k-1) ret.push_back(temp);
            else{
                ++i;
                temp[i] = temp[i-1];
            }
        }
        return ret;
    }
};
