题意：
给出两个排列好的数组，求出两个数组的中位数， time complexity should be O(log (m+n))

法1:两路归并排序 merge sort
T（n) = o(nlogn);
补充：
归并排序，也叫合并排序。它是建立在归并操作上的一种有效的排序算法，归并操作即将两个已经排序的序列合并成一个序列的操作。该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。
采用分治法的思路是：
（1）分解：将当前区间一分为二，即求分裂点；
（2）求解：递归地对两个子区间R[low..mid]和R[mid+1..high]进行归并排序；
（3）组合：将已排序的两个子区间R[low..mid]和R[mid+1..high]归并为一个有序的区间R[low..high]。
递归的终结条件：子区间长度为1（一个记录自然有序）。
把原区间一分为二，在相应的子集上再进行一分为二，直到子区间的长度为1。再对子区间进行合并，直到恢复原区间的长度。
代码实现：
#include<stdio.h>  
#include<stdlib.h>  
#define INFINITE 1000  
//归并排序  
void mergeSort(int *a,int start,int end)  
{  
    int mid=(start+end)/2;  
    if(start<end){  
        //分解  
        mergeSort(a,start,mid);  
        mergeSort(a,mid+1,end);  
        //合并  
        merge(a,start,mid,end);  
    }  
}  
//对两个序列进行合并,数组从mid分开  
//对a[start...mid]和a[start+1...end]进行合并  
void merge(int *a,int start,int mid,int end)  
{  
    int i,j,k;  
    //申请辅助数组  
    int *array1=(int *)malloc(sizeof(int)*(mid-start+2));  
    int *array2=(int *)malloc(sizeof(int)*(end-mid+1));  
  
    //把a从mid分开分别赋值给数组  
    for(i=0;i<mid-start+1;i++)  
        *(array1+i)=a[start+i];  
    *(array1+i)=INFINITE;//作为哨兵  
    for(i=0;i<end-mid;i++)  
        *(array2+i)=a[i+mid+1];  
    *(array2+i)=INFINITE;  
    //有序的归并到数组a中  
    i=j=0;  
    for(k=start;k<=end;k++){  
        if(*(array1+i) > *(array2+j)){  
            a[k]=*(array2+j);  
            j++;  
        }  
        else{  
            a[k]=*(array1+i);  
            i++;  
        }  
    }  
    free(array1);  
    free(array2);  
}  
时间复杂度分析：
总时间=分解时间+解决问题时间+合并时间。
分解时间就是把一个待排序序列分解成两序列，时间为一常数，时间复杂度o(1).
决问题时间是两个递归式，把一个规模为n的问题分成两个规模分别为n/2的子问题，时间为2T(n/2).
合并时间复杂度为o（n）。
总时间T(n)=2T(n/2)+o(n).
用递归树的方法解递归式T(n)=2T(n/2)+o(n):假设解决最后的子问题用时为常数c，则对于n个待排序记录来说整个问题的规模为cn。
第一层时间代价为cn，第二层时间代价为cn/2+cn/2=cn.....每一层代价都是cn，总共有logn+1层。所以总的时间代价为cn*(logn+1).时间复杂度是o(nlogn).
-------------------------------------------
法2：递归截断
思路：
1.要想找到两个数组合并起来的中位数，就是找到nums1+nums2的中位数的值
但是因为nums1+nums2的奇偶不好确定，因此用到一个小技巧left = (p+q+1)/2；right = (p+q+2)/2;再分别取（left+right）的中值
如果（left+right）为奇数，left和right两者的值相等
如果（left+right）为偶数，left和right两者的值取平均
2.想要找到合并数组中的middle元素，我们可以假设它存在于两个子数组的middle/2的位置，即对middle进行二分法搜索，从而进入递归
3.进入递归首先要确认边界终止条件
如果nums1或者nums2其中一个为空，那么直接从另一个数组中找到middle位置即可
如果middle的大小为1，那么返回两个数组中起点元素中较小的一个
如果在数组中存在middle/2位置的元素，取出；如果不存在，置为最大值；
进入递归，目标是找到一个数字，因此
如果第一个数组中的中位数小于第二个数组中的中位数，那么第一个数组中的前middle/2个元素中一定没有目标元素，将第一个数组后移middle/2。
如果第二个数组中的中位数小于第一个数组中的中位数，那么第二个数组中的前middle/2个元素中一定没有目标元素，将第二个数组后移middle/2。
4.不断缩小变量范围middle/2，直到得到递归终止条件
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int p = nums1.size();
        int q = nums2.size();
        int left = (p+q+1)/2;
        int right = (p+q+2)/2;
        return (getValue(nums1,nums2,left,0,0) + getValue(nums1,nums2,right,0,0))/2;
    }
    
    double getValue(vector<int>&nums1,vector<int>&nums2,int middle,int fir1,int fir2){
        int mid1;
        int mid2;
        if(fir1 >= nums1.size()) return nums2[fir2+middle-1];
        if(fir2 >= nums2.size()) return nums1[fir1+middle-1];
        if(middle == 1) return min(nums1[fir1],nums2[fir2]);
        if(fir1+middle/2-1< nums1.size()){
            mid1 = nums1[fir1+middle/2-1];
        }else{
            mid1 = INT_MAX;
        }
        if(fir2+middle/2-1< nums2.size()){
            mid2 = nums2[fir2+middle/2-1]; 
        }else{
            mid2 = INT_MAX;
        }
        if(mid1<mid2){
            return getValue(nums1,nums2,middle-middle/2,fir1+middle/2,fir2);
        }else{
            return getValue(nums1,nums2,middle-middle/2,fir1,fir2+middle/2);
        }
        
    }
};
遍历算法：【待学习】
https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2471/very-concise-ologminmn-iterative-solution-with-detailed-explanation
