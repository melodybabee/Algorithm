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

二刷：
方法1:创建新数组，把后面剩余的元素连在后面
注意：
1.在新数组中不需要再次用一个坐标计数，直接push_back即可
2.注意用两个原数组的指针来判断到没到结尾，擅用m,n不要判断是否为0
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int>ret;
        int i = 0;
        int j = 0;
        while(i < m && j < n){
            if(nums1[i] <= nums2[j]){
                ret.push_back(nums1[i]);
                ++i;
            }else{
                ret.push_back(nums2[j]);
                ++j;
            }
        }
        while(i < m){
            ret.push_back(nums1[i]);
            ++i;
        }
        while(j < n){
            ret.push_back(nums2[j]);
            ++j;
        }
        nums1 = ret;
    }
};
优化：
1.不占用新的空间，从尾部开始循环，注意要提前对m,n进行减1操作。
擅于利用m,n.
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int count = m+n-1;
        --m;
        --n;
        while(m >=0 && n >= 0){
            if(nums1[m] < nums2[n]) {
                nums1[count] = nums2[n];
                --n;
                --count;
            }else{
                nums1[count] = nums1[m];
                --m;
                --count;
            }
        }
        while(n >= 0){
            nums1[count] = nums2[n];
            --count;
            --n;
        }
    }
};