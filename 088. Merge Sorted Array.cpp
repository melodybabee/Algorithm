class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> ans(m+n,0);
        int count = 0;
        int i = 0,j = 0;
        while(i< m && j < n){
            if(nums1[i]<= nums2[j]){
                ans[count] = nums1[i];
                ++count;
                ++i;
                }
            else{
                ans[count] = nums2[j];
                ++count;
                ++j;
                }
            }
        while (i<m){
            ans[count] = nums1[i];
            ++count;
            ++i;
        }
        while (j<n){
            ans[count] = nums2[j];
            ++count;
            ++j;
        }
        nums1 = ans;
        
        
    }
};

/*
思路：
1.新建一个array(vector),array[m+n],分别循环nums1和nums2,比较大小
2.将小的数字放到新的array中，以此类推

注意：
1.边界条件是一个结束后而另一个还没有结束，就需要单独来处理尾巴
while(i< m && j < n)满足的时候按照谁小放谁的原则，如果谁有尾巴谁就继续，直到都到结尾之后return
2.连续声明两个变量的时候要分别赋值，int i = 0,j = 0;
*/
