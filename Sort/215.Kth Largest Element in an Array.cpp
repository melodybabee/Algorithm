题意：
找到array中第K大的值，不是元素。
思路一：priority_queue
1.在priority_queue中依次输入数组中的元素，在K之前不断pop出顶部的元素，最后返回堆顶元素。
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> q;
        int ret = 0;
        for(int i = 0; i < nums.size(); ++i){
            q.push(nums[i]);
        }
        for(int i = 1; i < k; ++i){
            q.pop();
        }
        ret = q.top();
        return ret;
    }
};
优化：
priority_queue可以通过数组的头部和尾部直接输入元素
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> q(nums.begin(),nums.end());
        for(int i = 1; i < k; ++i){
            q.pop();
        }
        return q.top();
    }
};
方法二：sort
注意题目中求的是第K大的值，不是第K大的数字，所以可以用排序，排序不去重。
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()-k];
    }
};
补充：
sort函数：
头文件： #include<algorithm>
		using namespace std;
时间复杂度：O(nlogn)
sort函数有三个参数：（第三个参数可选） 
第一个是要排序的数组的起始地址
第二个是结束的地址（最后一位要排序的地址）
第三个参数是排序的方法，可以是升序也可是降序。如果不写第三个参数，则默认的排序方法是从升序排列
第三个参数：
bool compare(int a, int b) {
    //return a < b;  //升序排列
    return a > b;  //降序排列
}
方法3:quick sort
思路：
1.因为题目中找第K大的数字，那么把所有大于目标值的数左移，把所有小于目标值的数右移，这样第K大的坐标就是k-1.
如果返回的坐标是k-1,那么返回当前值否则缩小左右边界范围再次调用快排
2.进入快排之后把头部结点固定，左小于固定点且右大于固定点，交换
最后把右边界与固定点交换
返回右坐标的位置
注意：
1.swap函数两个位置必须是坐标，不能是值
2.注意在快排判断的过程中，不含等号，如果相等只改变坐标不进行交换
3.本题因为求第K大，所以所有大于K的数字应该放在左侧
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int i = 0;
        int j = nums.size()-1;
        while(true){
            int pos = quickSort(i,j,nums);
            if(pos == k-1) return nums[pos];
            else if(pos > k-1) j = pos-1;
            else i = pos +1;
        }
    }
    
    int quickSort(int left, int right, vector<int>& nums){
        int goal = nums[left];
        int l = left +1;
        int r = right;
        while(l <= r){
            if(nums[l] < goal && nums[r] > goal){
                swap(nums[l],nums[r]);
                ++l;
                --r;
            }
            if(nums[l] >= goal) ++l;
            if(nums[r] <= goal) --r;
        }
        swap(nums[r],nums[left]);
        return r;
    }
};
方法4:堆排序方法待学习

12.11复习：
1.heap
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int>q;
        for(auto a:nums){
            q.push(a);
        }
        for(int i = 1; i< k;++i){
            q.pop();
        }
        return q.top();
    }
};
2.quick sort
注意：
1.交换结果是大的数字在前，小的数字在后，因此最后头结点进行交换的时候要与靠后的结点位置进行交换。
同时注意交换的是坐标上的值，而不单纯是值。
2.用汇合点或者是靠右的结点位置来判断是否是要找的位置。
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0; 
        int right = nums.size();
        while(left < right){
            int i = left;
            int j = right-1;
            int p = nums[left];
            while(i <= j){
                while(i <= j && nums[i] >= p) ++i;
                while(i <= j && nums[j] < p) --j;
                if(i < j) {
                    swap(nums[i],nums[j]);
                    ++i;
                    --j;
                }
            }
            swap(nums[left],nums[j]);
            if(j == k-1) return nums[j];
            else if(j < k-1) left = j+1;
            else right = j;
        }
    }
};

3.26复习：
1.STL sort
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()-k];
    }
};
2.priority_queue
注意：
priority_queue可以直接用(nums.begin(),nums.end())输入
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int>pq(nums.begin(),nums.end());
        int i = 1;
        while(i < k){
            pq.pop();
            ++i;
        }
        return pq.top();
    }
};
3.快排
注意：
1.快排需要在一个已经确定左右边界的大前提下继续建立左右边界，设置左边界为基准值【WHY？别的行不行】
因为快排其实应用的是分治法的思想，所以如果能把数组分成等长的长度其实效率是最高的。如果以第一个为基准元，当有序时，每次只能完成一次排序，所以时间复杂度回退化为O(N*N);
所以选择基准元有更好的方法，比如随机基准元或者三数取中【待学习】https://www.kancloud.cn/maliming/leetcode/740422
2.注意快排的边界：
因为第一个值是基准元，那么为了保证它的移动，需要在判断时候取等
3.因为需要建立左右边界，那么如果只有一个值不会进入while循环，因此把right = nums.size();在进入while循环之后再减1
4.本题是把大的数字移动到前面，小的数字移动到后面
5.在i与j相等的时候，要需要进入循环，因为需要与基准元进行交换的一定是大于基准元的元素，所以i，j重合的时候需要再次判断重合位置的值。
6.注意交换是位置上的值的互换，而不是与一定的值进行交换
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0;
        int right = nums.size();
        while(left < right){
            int i = left;
            int j = right-1;
            int cur = nums[left];
            while(i <= j){
                while(i <= j && nums[i] >= cur) ++i;
                while(i <= j && nums[j] < cur) --j;
                if(i < j){
                    swap(nums[i],nums[j]);
                    ++i;
                    --j;
                }
            }
            swap(nums[j],nums[left]);
            if(j == k-1) return nums[j];
            else if(j > k-1) right = j;
            else left = j+1;
        }
        return 0;
    }
};

