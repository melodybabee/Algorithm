/*
思路：
1.判断一个链表是不是环状的，有两种情况，一个是尾巴连头为闭环，一个是尾巴连任意一个结点，非闭环
2.可以建立一个vector，用于存放结点的地址,从链表头部开始循环，依次将循环到的结点push_back()到vector里
3.如果头部为空，则false，每循环到一个新的结点，从vector头部开始判断是否与此结点的地址相同，如果相同，true,不同，false

注意：
1.判断是不是相同的结点，需要看地址是否相同，而不是单纯比较值，因为会有值相同而地址不同的情况
2.同时每次都需要从vector头部开始循环，查找效率太低，本题运用这种方式会TLE。因此需要优化。
*/
*********************
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *p = head;
        set <ListNode*> nodes;
        if(p == NULL) return false;
        while(p->next){
            nodes.insert(p);
            if(nodes.count(p->next)){
                return true;
            }
            p = p->next;
        }
        return false;
    }
};
/*优化思路1：
1.将存储的结构更改为set,而不是vector
*********************
vector:
1.封装数组，对于随机访问的速度很快，,尾部插入的速度很快，头部很慢
2.连续内存存储，可以确定到某一位[]
*********************
list:
1.封装链表，对于随机访问的速度很慢，因为需要遍历整个链表才可以得到
2.插入很快，对指针改变指向即可，不需要拷贝和移动数据
3.线性非连续结构，不支持[]
*********************
set:
1.属于标准关联容器，用到了平衡检索二叉树，红黑树
	关于红黑树：
	1.红黑树本质上就是一棵二叉查找树
	二叉查找树（Binary Search Tree），也称有序二叉树（ordered binary tree）,排序二叉树（sorted binary tree），是指一棵空树或者具有下列性质的二叉树：
	*若任意结点的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
	*若任意结点的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
	*任意结点的左、右子树也分别为二叉查找树。
	*没有键值相等的结点（no duplicate nodes）
	2.一棵由n个结点，随机构造的二叉查找树的高度为lgn，所以顺理成章，一般操作的执行时间为O（lgn）
	3.红黑树，本质上来说就是一棵二叉查找树，但它在二叉查找树的基础上增加了着色和相关的性质使得红黑树相对平衡，从而保证了红黑树的查找、插入、删除的时间复杂度最坏为O(log n)
	*每个结点要么是红的，要么是黑的。  
	*根结点是黑的。  
	*每个叶结点（叶结点即指树尾端NIL指针或NULL结点）是黑的。  
	*如果一个结点是红的，那么它的俩个儿子都是黑的。  
	*对于任一结点而言，其到叶结点树尾端NIL指针的每一条路径都包含相同数目的黑结点。 
2.用于存储同一数据类型，与vector的区别在于不包含重复的元素
3.与链表相似，他的插入删除效率比其他序列容器高是因为不需要做内存拷贝和内存移动，而直接替换指向节点的指针即可，但是不是线性结构
4.Set和Map的区别在于Set只含有Key，而Map有一个Key和Key所对应的Value两个元素。
5.set常见用法：
	set.begin() = set.rend();返回容器的第一个元素
	set.end() = set.rbegin(); 返回容器的最后一个元素
	set.clear();清空
	set.empty();判断是否为空
	set.insert();插入一个元素
	set.max_size();返回可能包含的最大元素个数
	set.size();返回当前容器中的元素个数
	set.count();计算数值在set中出现的次数
	在first和second之间加入元素，insert(first,second);
*********************
map:
1.Set和Map的区别在于Set只含有Key，而Map有一个Key和Key所对应的Value两个元素。
Map和Hash_Map的区别是Hash_Map使用了Hash算法来加快查找过程，但是需要更多的内存来存放这些Hash桶元素，因此可以算得上是采用空间来换取时间策略。
*/
*********************
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while(fast){
            fast = fast -> next;
            slow = slow -> next;
            if(fast){
                fast = fast->next;
            }
            else{
                return false;
            }
            if(fast == slow){
                return true;
            }
        }
        return false; 
    }
};
/*
思路：
1.用龟兔赛跑算法，Floyd Tortoise-Hare Algorithm
2.设定快慢指针，两个人在环形跑道上同向而行，一前一后，速度不等，则快的那个一定能追上慢的那个。
3.因此只要当快指针存在时，快走2步，慢走1步，如果快走到了结尾还不与慢相等，则没有环
4.只要遇到了快与慢相等的情况，则有环
*/


2.25复习
1.最暴力的解法hashtable,也可以优化成set
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_map<ListNode*,int> m;
        while(head){
            if(m.count(head)){
                return true;
            }else{
                ++m[head];
            }
            
            head = head->next;
        }
        return false;
    }
};
Set做法：
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> s;
        while(head){
            if(s.find(head) != s.end()){
                return true;
            }else{
                s.insert(head);
            }
            
            head = head->next;
        }
        return false;
    }
};

快慢指针：
快慢指针找中点或者判断是否有环，while中的条件就是为了避免fast会移动到空的位置上。
如果一旦相遇，就直接返回true.if的判断需要在while里面。
注意会有空的情况。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(! head) return false;
        ListNode *slow = head;
        ListNode *fast = head;
        while(fast -> next && fast -> next -> next){
            slow = slow -> next;
            fast = fast -> next -> next;
            if(fast == slow){
                return true;
            }
        }
        return false;
    }
};