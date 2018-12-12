题意：
获取距离x最近的K个元素。
方法一：两侧删除
思路：
1.因为数组是排好序的，所以获取的数组应该是以x为中心的长度为k的数组，即删除长度为n-k长度的数组。
2.但是如果x不在范围内，那么就从最远的距离开始删除。
3.只要数组的长度大于k的长度，进入循环，比较x到左右两侧的距离，删除远的一侧。如果相同，删除右侧。
注意：
1.vector获取第一个元素，front()，获取尾部元素，back()
2.删除最后一个元素，pop_back(),删除第一个元素，erase(arr.begin())
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        while(arr.size() > k){
            if(x - arr.front() <= arr.back() - x ){
                arr.pop_back();
            }else{
                arr.erase(arr.begin());
            }
        }
        return arr;
    }
};
方法2:二叉搜索
思路：
1.因为k小于数组的长度，因此把数组长度-k设置为右边界。
2.每次取中间值，x到那边的距离远向其反方向移动。为了找到返回数组的左边界。最后重合的位置就是要找的左边界。
3.最后返回以重合点为左边界，长度为k的子数组。
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0;
        int right = arr.size()-k;
        while(left < right){
            int mid = left + (right-left)/2;
            if(x - arr[mid] > arr[mid+k] - x) left = mid+1;
            else right = mid;
        }
        vector<int>vec{arr.begin() + right, arr.begin() +right + k};
        return vec;
    }
};