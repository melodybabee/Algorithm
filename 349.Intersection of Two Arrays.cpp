题意：
合并两个array中相同的部分为一个vector
思路：
1.先将两个vector排序，这样方便排除重复的元素
2.再用两个for循环查找，外层循环如果重复就跳过，内层循环如果找到了就break避免重复
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ret;
        if(nums1.empty() || nums2.empty()) return ret;
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        int p = 0;
        for(int j = 0; j < nums1.size(); ++j){
            if(j > 0 && nums1[j] == nums1[j-1]) continue;
                for (int i = 0; i < nums2.size(); ++i){
                    if(nums2[i]  == nums1[j]){
                        ret.push_back(nums2[i]);
                        break;
                    }
                }
        }
        return ret;
    }
};