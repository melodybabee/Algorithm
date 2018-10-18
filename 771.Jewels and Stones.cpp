题意：
1.给一个J，里面的字符表示是珠宝，再给一堆石头S，里面可能有珠宝，求珠宝的个数。
方法1：暴力拆解，两轮for循环
思路：
1.两轮for循环，找一个字符串里面包含另一个字符串中字符的个数。
class Solution {
public:
    int numJewelsInStones(string J, string S) {
        int ret = 0;
        for(int i = 0; i< J.size();++i){
            for(int j = 0; j < S.size(); ++j){
                if(S[j] == J[i]) ++ret;
            }
        }
        return ret;
    }
};
方法2：hashset
知识补充：
unordered_map和map
unordered_map存储机制是哈希表,即unordered_map内部元素是无序的。
map是红黑树，map中的元素是按照二叉搜索树存储，进行中序遍历会得到有序遍历。是以key来查找value的，按照key排序。
unordered_set和set
unordered_set基于哈希表，是无序的。
头文件：#include<unordered_set>
 unordered_set<int> set;//定义一种数据类型
        for (int i=0; i<list.size(); i++){
            set.insert(list[i]);//set.insert()方法
        }
        for (unordered_set<int>::iterator i = set.begin(); i != set.end(); i++) {
            cout << *i << endl;
        }
        cout << " find 39: " << *set.find(39) << endl;//注意找到39的值，如果输出是值的话要用*
        cout << "count 14:" << set.count(5) << endl;//在set里面找5这个位置有没有数据，有为1，没有是0
介绍：std::unordered_set 是基于hash表的，因此并不是顺序存储
set实现了红黑树的平衡二叉检索树的数据结构，插入元素时，它会自动调整二叉树的排列，把元素放到适当的位置，以保证每个子树根节点键值大于左子树所有节点的键值，小于右子树所有节点的键值；另外，还得保证根节点左子树的高度与右子树高度相等。
平衡二叉检索树使用中序遍历算法，检索效率高于vector、deque和list等容器，另外使用中序遍历可将键值按照从小到大遍历出来。
class Solution {
public:
    int numJewelsInStones(string J, string S) {
        int ret = 0;
        unordered_set<char> set(J.begin(),J.end());
        for(auto &i : S){
            if(set.count(i)) ++ret;
        }
        return ret;
    }
};