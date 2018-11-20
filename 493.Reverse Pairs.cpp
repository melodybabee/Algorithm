题意：
在一个数组中找公有几对子数组满足i <j, 且nums[i] > 2*nums[j]。
方法一：暴力拆解
无法AC。TLE.
每次遇到int类型的数字乘积的时候需要考虑是否超过了int的范围。

【需要复习】方法二：binary indexed tree，顺序重现关系(Sequential Recurrence Relation)
T(n) = nlogn, S(n) = n
思路：
1.题目中的要求是使顺序上满足前后顺序，同时前面的数组大于后面数字的2倍。那么从后面向前循环，在当前位置之前的位置查找是否满足大小关系即可。
用式子表示是T(i, j) = T(i, j - 1) + C。
已知翻转对的第二个数字为nums[j], 在子数组nums[i, j - 1]中找翻转对的第一个数字，这里翻转对的两个条件中的顺序条件已经满足，就只需要找比2*nums[j]大的数即可。
2.形成上面的思路之后可以进行线性扫描，可以利用BIT大大提升计算效率。
3.首先创建一个哈希表，和一个bit数组，对原来的数组进行sort排序，使其由小到大进行排序。
4.在哈希表中记录下被排序数组中最后出现该数字的位置，对应输入到hashmap中。这一步是为了便于把数字的频次更新到BIT中，这样通过计算BIT的和，就可以知道有多少数字满足条件。
注意因为BIT是从1开始的，所以存入hashtable的时候就要在原数字的基础之上+1
5.开始从后向前遍历原数组，注意是遍历原数组，在已经被排序好的数组中找到不小于当前元素一半的元素的位置，跳转到BIT求和方法中进行求和。
同时更新BIT数组。
6.BIT求和方法即i大于0的前提下，相加，再依次递减i
7.更新BIT数组是在i不超过BIT数组的长度下，因此递增
注意：
1.lower_bound()方法
因为想通过这个方法求出第一个不大于指定元素一半的元素位置，其返回的是一个迭代器元素，如果想得到一个整数值，需要减去头部元素的位置，即v.begin()
2.map的初始化
注意map初始化要声明两个元素，不要在智障问题上出错
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        vector<int> v = nums;
        vector<int> bit(nums.size()+1);
        sort(v.begin(),v.end());
        unordered_map<int,int> map;
        int ret = 0;
        for(int i = 0; i< v.size();++i){
            map[v[i]] = i+1;
        }
        for(int i = nums.size()-1; i >= 0; --i){
            ret += getSum(lower_bound(v.begin(),v.end(),nums[i]/2.0)-v.begin(),bit);
            update(map[nums[i]],bit);
        }
        return ret;
    }
    
    int getSum(int i,vector<int>&bit){
        int ret = 0;
        while(i > 0){
            ret += bit[i];
            i -= (i&-i);
        }
        return ret;
    }
    
    void update(int i,vector<int>&bit){
        while(i < bit.size()){
            bit[i] += 1;
            i += (i&-i);
        }
    }
};

方法3:构造二叉搜索树
TLE,但是思路没有问题。315follow up
思路：
1.构造一个二叉搜索树，在结点记录原有值的同时，再增加一个变量记录有多少个数字大于等于本身
2.从头开始遍历，先查找，返回的数字就是有多少个数字大于等于本身，注意向左查找的时候应该加上根结点本身
3.对每个新遍历到的值再进行插入，同时增加countnum的值
4.最后返回总的个数值
注意：
1.因为一个数的2倍有可能会超过int范围，因此需要啊int变为long long，所以*2操作的时候的2为long long即可。*2LL
class Solution {
public:
    struct Node{
        int val;
        int countnum;
        Node *left;
        Node *right;
        Node(int v, int c): val(v), countnum(c),left(NULL), right(NULL){};
    };
    int reversePairs(vector<int>& nums) {
        int count = 0;
        Node *head = NULL;
        for(int i = 0; i < nums.size(); ++i){
            count += search(head,nums[i]*2LL+1);
            head = insert(head,nums[i]);
        }
        return count;
    }
    
    int search(Node *head, long long i){
        if(!head) return 0;
        else if(head -> val == i) return head->countnum;
        else if(head -> val > i) return head ->countnum + search(head->left, i);
        else{
            return search(head-> right, i);
        }
    }
    
    Node* insert(Node *head, int i){
        if(!head) return new Node(i,1);
        else if(head -> val == i) ++ head->countnum;
        else if(head -> val < i){
            ++head->countnum;
            head-> right = insert(head -> right, i);
        }
        else{
            head-> left = insert(head -> left, i);
        }
        return head;
    }
};

方法4:插入排序，分割重现关系(Partition Recurrence Relation)
T(n) = nlogn, S(n) = n
思路：
1.利用插入排序的思想，首先把原数组中的数字从中间开始一一分解
2.把最后分解的两个数组进行比较，设置一个i指向第一个数组头部，设置一个j指向第二个数组头部
在最底层中为两个元素，因此查找结束之后进行排序，以此类推，所有数组都会在比较值钱进行排序。
3.因为数组是排序好的，因此如果i不满足条件，那么直接向后移动i即可，不需要再向后移动j进行比较
如果i满足条件，那么向后移动j，记录的结果是j移动的距离
4.这样结果会分为三部分，左半部分的匹配对，右半部分的匹配对，和左右合并起来之后交叉的匹配对。自下向上进行加和。
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        return findSum(nums, 0, nums.size()-1);
    }
    int findSum(vector<int>& nums, int left, int right){
        if(left >= right) return 0;
        int mid = left + (right-left)/2;
        int res = findSum(nums, left, mid) + findSum(nums, mid+1,right);
        for(int i = left, j = mid+1; i <= mid; ++i){
            while(j <= right  && nums[i]/2.0 > nums[j])++j;
            res += j - (mid+1);
        }
        sort(nums.begin()+left,nums.begin()+right+1);
        return res;
    }
};

