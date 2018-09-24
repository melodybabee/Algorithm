思路：
1.建立hashtable, key表示原数组的值，value表示true／false
2.开始value为空，每到一个key判断是否是true,若是，则返回true;不是，将该位置写上true
3.如果遍历vector之后仍然没有返回true,返回false

T: O(n), S: O(n)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,bool> map;
        for(int i = 0; i < nums.size(); ++i){
            if(map[nums[i]] == true) return true;
            map[nums[i]] = true;
        }
        return false;
    }
};

也可以用两个for循环遍历T: O(n*2), S: O(1)或者sort()的方法T: O(1), S: O(nlogn)
还有一种更巧妙的解法：
bool containsDuplicate(vector& nums) {
    unordered_sets(nums.begin(),nums.end());
    int len1 = s.size(),len2 = nums.size();
    if(len1<len2)
        return true;
        return false;
}
运用set，这样相同的数字就会放在一个结点上，没有值重复的数字，因此最后比较sets的大小和原vector的大小是否相同就可以。

之前的答案：
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        if(nums.size() == 1) return false;
        if(nums.empty()) return false;
        
        for (int i = 0; i < nums.size() -1; ++i){
            for (int j = i+1; j < nums.size(); ++j)
                if(nums[i] == nums[j])
                    return true;
        }
        return false;
        
    }
};
/*
设计思路：
1.循环vector,如果一旦有相等，return true,否则return false
2.如果为0，return false
3.如果只有一个元素，return false

注意：
1.区分“=”和“==”
2.判断vector是否为空，要用nums.empty()

优化：
1.本题时间复杂度很高，注意后面的优化
*/
