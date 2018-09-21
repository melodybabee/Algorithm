class Solution {
public:
    bool isHappy(int n) {
        unordered_map<int,bool> map;
        int num = 0;
        map[n] = 1;
        while(n != 1){
            while(n){
                num += (n%10) * (n%10);
                n /=10;
            }
            if(map[num]) break;
            else map[num] = 1;
            n = num;
            num = 0;
        }
        return 1 == n;
    }
};
//HashMap,
思路：
1.建立一个散列表，key表示数值，value表示该数值是否存在
2.首先把原始值n设为存在，如果n最后的结果为1，则为happynum,如果n不为1但在hash表中已经出现过该元素，则为unhappynum
3.当n不为1的时候不断循环，内部循环表示从n的个位开始依次进行squares of its digits
4.如果新的数字位置在hash表中存在，跳出循环，比较该数与1是否相等，否则将表中该位的值置为1
5.不断更迭直到n==1为止
注意：
1.除了return一行的1为数值以外，其余的1表示"存在"含义，即map->first为n值，其多对应的map->second已经被占上
2.因为运算顺序num += (n%10) * (n%10);要加括号，num += n%10 * n%10;是错的

class Solution {
public:
    bool isHappy(int n) {
        int num = 0;
        while(n != 1 && n!= 4){
            while(n){
                num += (n%10) * (n%10);
                n /=10;
            }
            n = num;
            num = 0;
        }
        return 1 == n;
    }
};
思路：
1.通过观察发现，只有遇到4的时候是unhappynum，会无限循环下去,因此如果n最终为1，true，其中等于4，false

**********************************************
知识补充：
1.unordered_map和map（哈希表和map)
unordered_map存储机制是哈希表，即unordered_map内部元素是无序的。
map是红黑树，map中的元素是按照二叉搜索树存储，进行中序遍历会得到有序遍历。
2.nordered_set和set
unordered_set基于哈希表，是无序的。
set实现了红黑树的平衡二叉检索树的数据结构，插入元素时，它会自动调整二叉树的排列，把元素放到适当的位置，以保证每个子树根节点键值大于左子树所有节点的键值，小于右子树所有节点的键值.
另外，还得保证根节点左子树的高度与右子树高度相等。
3.unordered_map
头文件：#include<unordered_map>
std::unordered_map 就是以key来查找value而设计,不会根据key排序。
声明：unordered_map<int, int> map; 第一个int表示哈希表中的位置，第二个int表示该位置上的值
例如已经创建了一个vector<int>list(5,14,34,22,29,5);
unordered_map<int, int> map;//创建哈希表
        for (int i=0; i<list.size(); i++){
            map[i] = list[i];
        }//将list中过的元素依次存入map中，对应的应该是：
        /*
        (0,5
         1,14
         2,34
         3,22
         4,29
         5,5)
        */
        cout << map[0] << endl;
        //输出map第0位上的值：5
        for (unordered_map<int, int>::iterator i = map.begin(); i != map.end(); i++){
            cout << i->first << ' ' << i->second << endl;
        }//简历迭代器i，从map头部依次开始循环，输出为
        /*
        5 5
        4 29
        3 22
        2 34
        1 14
        0 5
		*/
        if (map.find(3) != map.end()) {
            cout << "find key=" << map.find(3)->first << ", value=" << map.find(3)->second << endl;
        }//key表示为map->first,value表示为map->second
        //3, 22
        if (map.count(5) > 0) {
            cout << "find 5: " << map.count(5) << endl;
        }
        //m.count(n)计算下标为n的位置有无数据，有返回1，无返回0。
4.map
头文件：#include<map>
std::map 就是以key来查找value而设计，根据key排序。
map<int, int> map1;
        for (int i=0; i<list.size(); i++){
            map1[i] = list[i];
        }
        for (map<int, int>::iterator i = map1.begin(); i != map1.end(); i++){
            cout << i->first << ' ' << i->second << endl;
        }
        if (map1.find(3) != map1.end()) {
            cout << "find key=" << map1.find(3)->first << ", value=" << map1.find(3)->second << endl;
        }
        if (map1.count(5) > 0) {
            cout << "count 5: " << map1.count(5) << endl;
        }
输出：
0 5
1 14
2 34
3 22
4 39
5 5
find key=3, value=22
count 5: 1


