evict驱逐
题意：
实现一个LRU缓存器，LRU is Least Recently Used.
方法：
1.首先理解这个数据结构的作用：
LRU中有两个方法，一个是get，一个是put.
其中get函数是通过输入key来获得value,如果成功获得后，这对(key,value)将会升至缓存器的顶部，称为常用对;如果不存在，将返回-1
put函数是指插入一对新的(key,value),如果原LRU中有这个key,那么需要先删除之前的，把新的插入到顶部，如果不存在，直接插入到顶部。
如果插入的数量超过了LRU的大小，那么删除LRU中底部的值。
2.因为题目中已经创建好了LRUCache对象，因此对于LRUCache这个对象需要创建三个私有变量。
(1)cap来确定LRU的大小。
(2)设定一个list里面存放(key,value)的pair对形式的迭代器
(3)用一个hashtable来记录key与pair的关系，便于查找
3.首先在LRUCache(int capacity)结构中确认LRU的大小
4.在put方法中，首先在map中查找这个key是否存在，如果存在，删除，重新从前插入list
如果cache的内存已经满了，那么找到list中的最后一个元素，pop_back(),再在map中删除这个key元素
5.在get方法中，首先遍历map,如果在map中不存在这个元素，返回-1.
如果找到了，在list的头部位置插入map中的key对应的list，即把这个pair放到顶部，返回这个pair的数值
补充：
1.list
Lists将元素按顺序储存在链表中,与向量(vectors)相比,它允许快速的插入和删除，但是随机访问却比较慢.
std::list<int>::iterator it，设置一个迭代器it来进行迭代访问list
assign() 给list赋值 
back() 返回最后一个元素 
begin() 返回指向第一个元素的迭代器 
clear() 删除所有元素 
empty() 如果list是空的则返回true 
end() 返回末尾的迭代器 
erase() 删除一个元素 
front() 返回第一个元素 
get_allocator() 返回list的配置器 
insert() 插入一个元素到list中 
max_size() 返回list能容纳的最大元素数量 
merge() 合并两个list 
pop_back() 删除最后一个元素 
pop_front() 删除第一个元素 
push_back() 在list的末尾添加一个元素 
push_front() 在list的头部添加一个元素 
rbegin() 返回指向第一个元素的逆向迭代器 
remove() 从list删除元素 
remove_if() 按指定条件删除元素 
rend() 指向list末尾的逆向迭代器 
resize() 改变list的大小 
reverse() 把list的元素倒转 
size() 返回list中的元素个数 
sort() 给list排序 
splice() 合并两个list 
swap() 交换两个list 
unique() 删除list中重复的元素
2.list的splice()方法：
举例：
std::list<int> mylist1, mylist2;.//创建myList1,myList2
std::list<int>::iterator it;//设置一个迭代器便于循环
// set some initial values:
for (int i=1; i<=4; ++i)
	mylist1.push_back(i);      // mylist1: 1 2 3 4
for (int i=1; i<=3; ++i)
    mylist2.push_back(i*10);   // mylist2: 10 20 30
it = mylist1.begin();
++it;                         // points to 2
mylist1.splice (it, mylist2); //在myList1的it位置插入myList2
// mylist1: 1 10 20 30 2 3 4
// mylist2 (empty)
// "it" still points to 2 (the 5th element)
//此处的it由于是指向的mylist1,splice后，此迭代器依然存在于mylist1中，故而不失效
mylist2.splice (mylist2.begin(),mylist1, it);//在mylist2中的begin()位置插入mylist1 it指向的位置
//由于it指向的地址被插入到mylist2中，而使迭代器it失效
// mylist1: 1 10 20 30 3 4
// mylist2: 2
// "it" is now invalid.
3.pair
pair是将2个数据组合成一个数据，当需要这样的需求时就可以使用pair。
(1）STL中的map就是将key和value放在一起来保存。
(2）另一个应用是，当一个函数需要返回2个数据的时候，可以选择pair。
pair实质上是一个结构体，其主要的两个成员变量是first和second，这两个变量可以直接使用。初始化一个pair可以使用构造函数，也可以使用std::make_pair函数，make_pair函数的定义如下：
template pair make_pair(T1 a, T2 b) { return pair(a, b); }
注意make_pair函数会将second变量都转换成double类型。
double精度高，有效数字15-16位，float精度低，有效数字6-7位，但是double消耗的内存是float的两倍，运算速度比float慢得多，建议能用float保证精度的就用float，少用double。
map是一个关联容器，里面存放的是键值对，容器中每一元素都是pair类型，通过map的insert()方法来插入元素(pair类型)。
4.rbegin()
迭代器begin(), end(), rbegin(), rend()都是指针。
其中begin()指向第一个元素，end()是指向最后一个元素的下一个。这就是为什么我们在使用map或是unordered_map来查找某个值时都要和end()比较呢，因为如果等于end()了，则说明所有的元素都遍历过一遍了，也包括最后一个元素。
rbegin()指向最后一个元素，rend()指向第一个元素，和begin()相等。
class LRUCache {
private:
    int cap;
    list<pair<int,int>>l;
    unordered_map<int, list<pair<int,int>>::iterator> m;
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        auto it = m.find(key);
        if(it == m.end()) return -1;
        l.splice(l.begin(),l,it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        auto it = m.find(key);
        if(it != m.end()) l.erase(it->second);
        l.push_front(make_pair(key,value));
        m[key]= l.begin();
        if(m.size() > cap){
            int k = l.rbegin()->first;
            l.pop_back();
            m.erase(k);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

3.26复习：
思路：
1.首先根据时间复杂度考虑，因为需要O（1）的时间复杂度，因此需要查找，并把其中的元素放在头部的位置，因此需要用到list的数据结构
同时需要O(1）复杂度的查找，所以需要用到hashtable
用两个数据结构，hashtable中的key是key,value是一个list,同时还有一个单独的list
2.get方法的核心是，先判断是否有这个元素，如果没有的话返回-1，如果有，那么把这个元素在list中移动到头部
list移动到头部的方法是l.splice(想移动到的位置，从哪里移动，移动什么)；
再输出对应map中value paie中的第二个value值
3.put方法的核心是，先判断是否有该key元素，如果有，那么在list中删除
如果不在起始位置删除，那么如果有重复的元素，会在map中直接覆盖，但是list中没有删除，不能保证统一
在list的头部重新添加进去这个pair
map中对应上key与这个list的头部元素
如果map中的元素个数大于规定值了，那么删除list的末尾元素，同时把在map中对应的元素也一并删除
4.list操作
push_front()从头部插入
erase()删除
splice（）移动到指定位置上
pop_back()弹出最后一个元素
5.pair操作
make_pair()用来初始化
6.list<pair<int,int>>::iterator建立迭代器，因为l.splice(l.begin(), l, it->second);中it->second就是需要是迭代器的格式
用迭代器来依次取值

class LRUCache {
private:
    list<pair<int,int>> l;
    unordered_map<int,list<pair<int,int>>::iterator> m;
    int cap;
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        auto it = m.find(key);
        if(it == m.end()) return -1;
        //remove this pair to the front
        l.splice(l.begin(), l, it->second);
        return it -> second -> second;
    }
    
    void put(int key, int value) {
        auto it = m.find(key);
        if(it != m.end()) l.erase(it->second);
        l.push_front(make_pair(key,value));
        m[key] = l.begin();
        if(m.size() > cap){
            int tempkey = l.rbegin()->first;
            l.pop_back();
            m.erase(tempkey);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */