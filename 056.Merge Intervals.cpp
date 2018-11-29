题意：给一些数组，合并所有overlapping的部分
方法一：先排序再汇合
T(n) = nlogn + n
思路：
1.因为题目中给出的数组不一定是有序的，所有对数组通过头结点由小到大排序
注意因为类型是自定义的Interval,因此需要复写排序方法，自定义一个struct
struct compInterval{
        bool operator()(const Interval &a, const Interval &b)const{
            return a.start < b.start;
        }
    };
2.vector中放入第一个数组，从vector头部开始循环，如果已经存在的数组的尾部元素小于循环数组的头部元素，那么正常push
如果大于，那么已经放入数组的尾部元素是它本身和下一个数组尾部元素中较大的一个
注意：
1.c++中调用结构题中的属性也可以用X.X	
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    struct compInterval{
        bool operator()(const Interval &a, const Interval &b)const{
            return a.start < b.start;
        }
    };
    vector<Interval> merge(vector<Interval>& intervals) {
        if(intervals.empty()) return{};
        sort(intervals.begin(),intervals.end(),compInterval());
        vector<Interval> ret{intervals[0]};
        for(int i = 1; i< intervals.size();++i){
            if(ret.back().end < intervals[i].start){
                ret.push_back(intervals[i]);
            }else{
                ret.back().end = max(ret.back().end,intervals[i].end);
            }
        }
        return ret;
    }
};
方法二：建立两个数组分别存头部元素和尾部元素，再分别push进去
思路：
1.分别用两个数组储存原数组的头部元素和尾部元素，排序
2.用两个指针i和j，初始化时分别指向starts和ends数组的首位置，然后如果i指向starts数组中的最后一个位置，或者当starts数组上i+1位置上的数字大于ends数组的i位置上的数时，此时说明区间已经不连续了
starts:   1    2    8    15
ends:     3    6    10    18
如果此时starts[i+1]为8，ends[i]为6，8大于6，所以此时不连续了，将区间[starts[j], ends[i]]，即 [1, 6] 加入结果res中，然后j赋值为i+1继续循环
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        int n = intervals.size();
        vector<int>start,end;
        vector<Interval>ret;
        for(int i = 0;i < n;++i){
            start.push_back(intervals[i].start);
            end.push_back(intervals[i].end);
        }
        sort(start.begin(),start.end());
        sort(end.begin(),end.end());
        for(int i = 0, j = 0;  i< n ;++i){
            if( i == n-1 || start[i+1] > end[i]){
                ret.push_back(Interval(start[j],end[i]));
                j = i+1;
            }
        }
        return ret;
    }
};
知识补充：排序【堆排序待学习】
--------------------------------------------
桶排序bucket sort：
思路：
1.有一个数量为n的数组A，数组的范围是0-Max.我们创建一个大小为Max+1的数组B，全部置为0。注意0-Max的个数为Max+1个。
2.从头开始遍历A，当读到A[i]的时候，B[A[i]]的值就加1。
3.当A遍历结束之后，扫描B，就能得到排序好的结果。
每个桶的含义事实上属于“标记”，即每个数字出现的次数，因此数组B通常称为book[].
复杂度：T(n) = O(M+N),M为桶的个数，N为待排序的个数
分析：桶排序适合数据量不大的排序，桶的个数需要占据很大的空间，如果不是整数很难操作
核心代码：
#include <iostream>
using namespace std;
void BucketSort(int *A, int Max, int Size){
    int B[Max+1];
    int i,j,count = 0;
    memset(B, 0, (Max+1)*sizeof(int));//把B的(Max+1)个元素置为0.memset:作用是在一段内存块中填充某个给定的值，它对较大的结构体或数组进行清零操作的一种最快方法。
    for (i = 0; i < Size; i++) {
        j = A[i];
        B[j] += 1;
    }
    for (i = 0; i <= Max; i++) {
        if (B[i] > 0) {
            for (j = 0; j < B[i]; j++) {
                A[count] = i;
                count++;
            }
        }
    }
}
int main(int argc, const char * argv[])
{
    int A[]={1, 2, 2, 7, 4, 9, 3, 5};
    int Max = 9; //这里可以用一个O(n)的函数来实现，假如数组的手动输入的，则在输入的时候就可以获取到。这里直接赋值是为了排出别的因素，看着简单。
    int Size = sizeof(A)/sizeof(int);
    BucketSort(A, Max, Size);
    for (int i = 0; i < Size; i++) {
        printf("%d ",A[i]);
    }
    printf("\n");
    return 0;
}
--------------------------------------------
冒泡排序：bubble sort
思路：每次比较两个相邻的元素，如果他们的顺序错误，就把他们交换过来。
复杂度：T(n) = O(n^2);
分析：时间复杂度较高
核心代码：
#include<iostream>
using namespace std;
//冒泡排序
void bubbleSort(int arr[], int n)
{
	for(int i = 0;i < n;i++){  
		//比较两个相邻的元素   
		for(int j = 0;j < n-i-1;j++){  
            if(arr[j] > arr[j+1]){  
                int t = arr[j];  
                arr[j] = arr[j+1];  
                arr[j+1] = t; 
                //上面三步也可以不用t
                //arr[j] += arr[j+1];
                //arr[j+1] = arr[j] - arr[j+1];
                //arr[j] -= arr[j+1];
            }  
        }  
    }       
}

int main(){
	int i;
	int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 10};
	bubbleSort(a,10);
	for(i=0;i<=9;i++)
	{	
		cout<<a[i]<<' ';
	}
	return 0;
}
--------------------------------------------
快速排序：quick sort【待学习不同基准位置的选择】
思路：每次找到一个基准数，在当前序列中，把所有大于基准数的放在右侧，所有小于基准数的放在左侧
复杂度：最坏的时间复杂度是T(n) = O(n^2);因为快排基于二分的思想，因此平均的时间复杂度是T(n) = O(nlogn)
分析：基准可以定为任何一个数字，但是如果基准定在第一个位置，那么第一个while循环必须从基准的对面开始，也就是最后一个位置，不然左右指针相遇的地点不能满足左小于基准，右大于基准。
核心代码：
void quickSort(int *arr,int l,int r)
{
	int i,j,x,temp;
	if(l > r) return;
	temp = arr[l]
	i = l;
	j = r;
	while(l<r)
	{
		while(i<j&&arr[j] >= temp)//找到第一个小于temp的数字
			j--;
		while(i<j&&arr[i]<=temp)//找到第一个大于temp的数字
			i++;
		if(i<j)
		{
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp; 
			//交换 
		}
	}
		arr[left] = arr[i];//i,j相遇之后交换相遇点的值和基准数的值。
		arr[i]= temp;
		quickSort(arr,l,i-1); //对左半部分进行快排 
		quickSort(arr,j+1,r); //对右半部分进行快排 
	}
}
int main(){
	int i;
	int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 10};
	quickSort(a,0，9);
	for(i=0;i<=9;i++)
	{	
		cout<<a[i]<<' ';
	}
	return 0;
}
--------------------------------------------
插入排序：Insertion sort
思路：从左开始进入循环，在第一层循环的位置进入第二层循环，将当前位置与之前位置比较，如果比前面的位置小就交换，直到回到头部的位置
复杂度：T(n) = O(n^2);
核心代码：
void insert_sort(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); i++) {
        for (int j = i; j > 0; j--) {
            if (nums[j] < nums[j - 1]) {
                int temp = nums[j];
                nums[j] = nums[j - 1];
                nums[j - 1] = temp;
            }
        }
    }
}
--------------------------------------------
选择排序：Selection sort
思路：从左开始进入循环，找到数组中最小的元素，与最左侧的元素进行交换，从已交换的位置开始下一次循环
复杂度：T(n) = O(n^2);
核心代码：
void selection_sort(vector<int> &nums)
{
    for (int i = 0; i < nums.size(); i++) {
        int min = i;
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[j] < nums[min]) {
                min = j;
            }
        }
        int temp = nums[i];
        nums[i] = nums[min];
        nums[min] = temp;
    }
}
--------------------------------------------
归并排序：Merge sort（004题中有应用）
思路：把原区间一分为二，在相应的子集上再进行一分为二，直到子区间的长度为1。再对子区间进行合并，直到恢复原区间的长度。
复杂度：T（n) = o(nlogn);打散过程是二分的，因此是logn，一共有n个数字，复杂度是n
分析：是采用divide and conquer的一个典型的例子，当数量级比较小的时候用插入排序更快。
核心代码：
void merge_array(vector<int> &nums, int b, int m, int e, vector<int> &temp)
{
    int lb = b, rb = m, tb = b;//合并
    while (lb != m && rb != e)
        if (nums[lb] < nums[rb])
            temp[tb++] = nums[lb++];
        else
            temp[tb++] = nums[rb++];

    while (lb < m)
        temp[tb++] = nums[lb++];
    
    while (rb < e)
        temp[tb++] = nums[rb++];

    for (int i = b;i < e; i++)
        nums[i] = temp[i];
}

void merge_sort(vector<int> &nums, int b, int e, vector<int> &temp)
{
    int m = (b + e) / 2;
    if (m != b) {
        merge_sort(nums, b, m, temp);//分解
        merge_sort(nums, m, e, temp);
        merge_array(nums, b, m, e, temp);
    }
}
--------------------------------------------
希尔排序：Shell sort
思路：先将整个待排元素序列分割成若干个子序列（由相隔某个“增量”的元素组成的）分别进行直接插入排序。
然后依次缩减增量再进行排序，待整个序列中的元素基本有序（增量足够小）时，再对全体元素进行一次直接插入排序。
因为直接插入排序在元素基本有序的情况下（接近最好情况），效率是很高的，因此希尔排序在时间效率上比插入排序高很多。
核心代码：
void ShellSort()
{
	int gap = len/ 2;//初始增量为数组长度的一半
	while (1 <= gap) 
	{
		for (int i = gap; i < len ; i++) 
		{
			int j = 0;
			int temp = iRawBuff[i];
			for (j = i - gap; j >= 0 && temp < iRawBuff[j]; j = j - gap)
			{
				iRawBuff[j + gap] = iRawBuff[j];
			}
			iRawBuff[j + gap] = temp;
		}
		gap = gap / 2; //增量为上次的二分之一
	}
	for (int k = 0; k < len; k++)
	{
		cout << iRawBuff[k] << "   ";
	}
	cout << endl;
}
--------------------------------------------
堆排序heap sort：
思路：
1.首先建立堆，如果从小到大排序，那么建立最小堆；如果从大到小排序，那么建立最大堆。
2.比如从小到大排序，那么每次删除堆顶元素或者把顶部元素输出放到一个新的数组中去，重新调整堆中剩余的元素，直到栈空为止。输出的就是由小到大排列的元素。
建堆：
1.可以从空堆开始，依次往堆里插入元素，直至都被插入到堆中为止。插入／删除一个元素的复杂度是logn,那么插入所有元素的复杂度是nlogn
2.更快的建堆方法是首先将结点从左到右从上到下开始1-n编码，从而转换为完全二叉树。
从最后一个非叶子结点开始向下调整，结点编号为n/2，直至符合堆的特性。
注意：
将堆的内容填入一个一位数组，这样通过下标就能计算出每个结点的父子节点，编号顺序从0开始，从左往右，从上至下层次遍历。a[10] = {2,8,5,10,9,12,7,14,15,13}
若一个结点的下标为k，那么它的父结点为(k-1)/2，其子节点为2k+1和2k+2

堆排序(Heap Sort)的时间复杂度是O(nlogn), 最坏情况下也是如此.
而快速排序(Quick Sort), 若初始记录序列有序, 快速排序将退化为起泡排序(Bubble Sort), 时间复杂度是O(n^2).这是堆排序比快速排序的优点.
代码：
#include <iostream>
#include <stack>
#include <queue>
 
using namespace std;
 
void HeapAdjust (int data[], int length, int k)
{
    int tmp = data[k];
    int i=2*k+1;
    while (i<length) {
        if (i+1<length && data[i]>data[i+1]) //选取最小的结点位置
            ++i;
        if (tmp < data[i]) //不用交换
            break;
        data[k] = data[i]; //交换值
        k = i; //继续查找
        i = 2*k+1;
    }
    data[k] = tmp;
}
 
void HeapSort (int data[], int length)
{
    if (data == NULL || length <= 0)
        return;
    for (int i=length/2-1; i>=0; --i) {
        HeapAdjust(data, length, i); //从第二层开始建堆
    }
 
    for (int i=length-1; i>=0; --i) {
        std::swap(data[0], data[i]);
        HeapAdjust(data, i, 0); //从顶点开始建堆, 忽略最后一个
    }
 
    return;
}
 
int main (void)
{
    int data[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int length = 8;
    HeapSort(data, length);
    for (int i=0; i<length; ++i) {
        std::cout << data[i] << " ";
    }
 
    std::cout << std::endl;
    return 0;
}
输出：
97 76 65 49 49 38 27 13 
堆排序的应用：
比如找数列中过的第K大数字，只要建立一个大小为K的最小堆，堆顶就是第K大数字。
例如在10个数字中找第3大数字，那么首先选取3个数字，比如前3个，将这三个数字建成最小堆，从第4个数字开始，与堆顶开始比较，如果小则不要，如果比堆顶大，那么舍弃当前堆顶元素插入新的值，再重新维护最小堆。
复杂度：T（n） = O（NlogK）；
