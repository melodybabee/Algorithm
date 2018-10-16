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
