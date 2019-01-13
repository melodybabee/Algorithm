题意：根据坐标找到离原点距离较近的K个点的坐标值
思路：map
1.直接比较平方值就可以，用map来对值和坐标的位置形成映射，map会自动排序，且可以重复。
那么map最适用于本题
2.在更新完map之后，从map的头部开始向结果数组中输入元素，注意因为map中的value是指的坐标，因此要向原数组中取值
最后当K为0的时候输出结果数组
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<vector<int>>ret;
        map<int,int>map;
        for(int i = 0; i< points.size(); ++i){
            int temp = pow(points[i][0],2)+pow(points[i][1],2);
            map[temp] = i;
        }

        for(auto it = map.begin(); K > 0; ++it, --K){
            ret.push_back(points[it->second]);
        }
        return ret;
    }
};
方法2:直接sort using heap
思路：
1.对原有数组直接进行排序，自定义排序方法，最后返回前K个
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        sort(points.begin(),points.end(),[](vector<int>&a,vector<int>&b){
            return a[0]*a[0]+a[1]*a[1] <= b[0]*b[0]+b[1]*b[1];
        });
        return vector<vector<int>>(points.begin(),points.begin()+K);
    }
};
注意：
1.一直到考虑如果把计算结果和坐标值连接起来，同时对计算的结果进行排序。
但是map的性质就是会自动排序，利用好这一点就不用纠结sort的问题
2.map从头部获得元素的方法要用到迭代器，建立一个it = map.begin()，it.second表示值，对于迭代器来说，可以修改实值，而不能修改key。
【问题】注意如果K的个数大于点的个数，比如[[1,3],[1,3]]，5。那么迭代器的返回的结果会是0，1，0，1，0，通过++it不断循环
3.再区分一次unordered_map,map,unordered_set,set
unordered_map存储机制是哈希表，，即unordered_map内部元素是无序的。
map是红黑树，map中的元素是按照二叉搜索树存储，进行中序遍历会得到有序遍历。因此根据key值快速查找记录，查找的复杂度基本是Log(N)
unordered_set基于哈希表，是无序的。
set实现了红黑树的平衡二叉检索树的数据结构，插入元素时，它会自动调整二叉树的排列，把元素放到适当的位置，以保证每个子树根节点键值大于左子树所有节点的键值，小于右子树所有节点的键值；另外，还得保证根节点左子树的高度与右子树高度相等。
map和set会进行自动排序，MAP的节点是一对数据，SET的节点是一个数据.
Map使用关键值Key来唯一标识每一个成员 map可以重复。set是集合会自动去重。
4.double的思路是很好的，但是本题中的数值范围是-10000 < points[i][0] < 10000，最多会形成200000000，也不会超过2147483648的int范围，这个是2的31次幂
遇到这种范围的题亲自估算一下，不要想当然，不然处理double数据不论代码还是心里上都会感觉提高了难度


Weekly Contest 119总结：
1.这次只AC一题，好不容易逐渐上来的排名又得下去，但是又高兴又生气。
高兴是因为这四道题现在都有思路了，起码不觉得难了。
生气的原因就很多了，一些细小的知识点掌握不牢；需要高效解体的思路还是不明朗；做过的题换了个马甲就不能AC，还是印象那么深刻的OA的题目......
这也对得起前几天没有像准备面试一样的强度刷题，来个下马威也是个好事吧。一道一道题说。
2.首先第一道3分的easy题就没有做出来。
unordered_map,map,unordered_set,set的区分不熟。知道应用场景，但是细分区别不能立刻、马上说的明明白白。
还考虑用priority_queue,奈何不会对vector<vector<int>>形式的进行排序，还要改为从小到大排序
3.第二题需要找子区间的题目首先想到了双指针，但是没有很好的解决问题。
虽然后面用到了DP，但是仍然是O（n^2）的时间复杂度，需要学习好的写法。
4.第三题是G的OA题目，应该可以算原题了，按照之前的思路写到一半才发现有变化，而且当时研究挺明白的题目现在也不是立现解法。
说明：要勤于复习；遇到问题还是要强化思考，不论难或者易；不要想当然
需要鼓励的是今天发现这是一道hard题目，当时研究的时候花了一些心思，说明只要肯于钻研是一定能研究透研究明白的，不要懒，尤其脑子
5.最后是一个三角形的题目，暴力解，学习更好的解法