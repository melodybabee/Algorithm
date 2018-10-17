题意：
对一个数组中的所有数字进行全排列
法一：回溯
思路：
1.依然运用回溯的方法，与combinations那道题（077）不同的是combination不同的顺序只算一种
比如找1-4之间的2位组合数，12，13，14，23，24，34共六个
但是如果对[1,2]进行全排列，那么12，21算两种
因此在本题中进行回溯的时候，每次都需要从头部开始，用一个bool数组记录这个数字是否被访问过
在返回尾部元素的时候还需要把这个数字重新置为false
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> temp;
        vector<vector<int>> ret;
        vector<bool>flag(nums.size()-1,false);
        dfs(nums,0,temp,ret,flag);
        return ret;
    }
    void dfs(vector<int>& nums,int start,vector<int>&temp,vector<vector<int>>&ret,vector<bool>&flag){
        if(start == nums.size()) return ret.push_back(temp);
        else{
            for(int i = 0; i < nums.size();++i){
                if(flag[i] == false){
                    flag[i] = true;
                    temp.push_back(nums[i]);
                    dfs(nums,start+1,temp,ret,flag);
                    temp.pop_back();
                    flag[i] = false;
                }
            }
        }
    }
};
法二：交换递归【需要二次理解】
先是最后两位交换，回到初始顺序，前两位交换
输出顺序为：123,132,312,321,231,213
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > res;
        permuteDFS(num, 0, res);
        return res;
    }
    void permuteDFS(vector<int> &num, int start, vector<vector<int> > &res) {
        if (start >= num.size())
            res.push_back(num);       
        for (int i = start; i < num.size(); ++i) {
            swap(num[start], num[i]);
            permuteDFS(num, start + 1, res);
            swap(num[start], num[i]);
        }
    }
};