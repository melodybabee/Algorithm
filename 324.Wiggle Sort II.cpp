题意：
280 follow up，扭动排序但是相邻两点不能相等
思路1:先排序再替换
T(n) = O(nlogn),S(n) = O(n);
1.
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        vector<int> temp = nums;
        sort(temp.begin(),temp.end());
        int mid = (nums.size()+1)/2-1;
        int last = nums.size()-1;
        for(int i = 0; i < nums.size(); ++i){
            if(i % 2 == 0) nums[i] = temp[mid], --mid;
            else nums[i] = temp[last], --last;
        }
    }
};