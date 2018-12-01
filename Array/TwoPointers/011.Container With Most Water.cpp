题意：
给出一个数组，面积为两数之间的距离*较小值，求数组中的最大面积

思路1：暴力拆解
T(n) = O(n^2), S(n) = 1
1.重新描述题意的过程已经描述了思路，因为给了一个蓄水池的场景，将实际问题转化为编程问题即可暴力拆解
2.依次循环每个元素，找到以该元素为起点的最大面积，即（循环到的位置-起点位置）*两者之间较小的值
3.再找出所有循环中最大的面积
class Solution {
public:
    int maxArea(vector<int>& height) {
        int ret = 0;
        int temp = 0;
        for(int i = 0; i < height.size();++i){
            for(int j = i+1; j < height.size();++j){
                temp = min(height[i],height[j]);
                ret = max(ret,temp*(j-i));
            }
        }
        return ret;
    }
};

思路2:双指针，不断向内移动
T(n) = O(n), S(n) = 1
1.用双指针直接获取面积，最大的面积=两个指针之间的长度*指针指向的值的较小值
2.因为两个指针间的距离在不断缩小，横向变量上的减小只会导致面积的减小，那么如果想要更大的面积，只能在纵向上增大
3.因此对于两个指针指向的值，本身由较小值决定，因此比较两者之间较小的值，把较小的值向内移动试图去找到较大的值
4.最后返回所求面积中最大的那个
class Solution {
public:
    int maxArea(vector<int>& height) {
        int head = 0;
        int end = height.size()-1;
        int ret = 0;
        while(head < end){
            ret = max(ret, (end-head)*min(height[head],height[end]));
            height[head]< height[end]?++head:--end;
        }
        return ret;
    }
};

二刷：
Two Pointers
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0;
        int r = height.size()-1;
        int area = 0;
        while(l < r){
            area = max(area,min(height[l],height[r]) * (r-l));
            if(height[l] <= height[r]) ++l;
            else --r;
        }
        return area;
        
    }
};
