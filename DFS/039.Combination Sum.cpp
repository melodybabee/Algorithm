题意：
找到一个数组中和等于目标值的子数组，其中原数组中的每个元素可以反复使用。
思路：
1.正常解决此类问题的时候，通常会想到先反复添加一个数字的值，如果相等，放在vector中。如果超出了目标范围，那么退回最后一个元素，继续向后面循环。
如果第一个元素都被退回了，那么开始循环第二个元素。以此类推。
这种思路完全符合回溯的思想，运用回溯的思想就要想到运用递归。
2.递归首先需要想到边界结束条件，本题的思路是只要加上一个新的元素，就在目标值下面减去对应值。
如果target值小于0，说明没有找到，此时应该结束本次递归，同时退回vector的最后一个元素。
如果target正好等于0，说明已经找到一个，那么vector中push_back这个元素。再退回最后一个元素继续判断。
如果都不满足两者，说明target值仍然还有剩余，那么继续进入递归。
如果递归的for循环不满足判断条件，说明已经进入了最后位置，已经运行到此方法的结尾。上层如果仍有递归返回递归，没有直接返回到调用函数中。
注意：
vector中退回最后尾部元素运用pop_back()方法。
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ret;
        vector<int> temp;
        sort(candidates.begin(),candidates.end());
        dfs(candidates,target,0,ret,temp);
        return ret;
    }
    void dfs(vector<int>& candidates,int target,int start,vector<vector<int>> &ret,vector<int>&temp){
        if(target < 0) return;
        else if(target == 0) return ret.push_back(temp);
        else{
            for(int i = start; i < candidates.size();++i){
                temp.push_back(candidates[i]);
                dfs(candidates,target-candidates[i],i,ret,temp);
                temp.pop_back();
            }
        }
    }
};

2.6复习：
注意：
1.需要运用DFS进行递归，在分析题意的时候得知先要把第一个数字循环完毕再开始判断第二个，因此需要先对数组进行排序
2.DFS是递归，就需要有边界条件，那么每次递归从目标值开始相减，注意相减的这个思路。只要小于0，直接跳过返回；如果等于0，输入到新的结果数组中
3.用一个坐标记录下当前的位置，每次进入递归从当前位置开始遍历，DFS新的一轮遍历还是从当前位置开始
在递归结束之后需要把push_back()的新元素再pop_back()出来
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<vector<int>>ans;
        vector<int>ret;
        dfs(candidates,ans,ret,target,0);
        return ans;
    }
    
    void dfs(vector<int>& candidates,vector<vector<int>>&ans,vector<int>&ret,int target, int start){
        if(target < 0) return;
        else if(target == 0) ans.push_back(ret);
        else{
            for(int i = start; i < candidates.size(); ++i){
                ret.push_back(candidates[i]);
                dfs(candidates, ans, ret, target-candidates[i], i);
                ret.pop_back();
            }
        }
    }
};
