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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* p = head;
        ListNode *newlist = new ListNode(0);
        ListNode *q = newlist;
        
        while(p){
            if(p->val!= val){
                q -> next = p;
                q = q -> next;
                q -> next = NULL;
                p = p ->next;
            }
            else{
                p = p->next;
            }
        }
        return newlist -> next;
    }
};

思路：
1.首先建立一个新的链表，将newlist设置为head结点，q为新链表上从头部开始可以移动的结点指针
2.p为原链表上的可移动指针，当p存在时，与规定值进行比较，如果不等，q->next接在p上，相等的话跳过
3.直到p不存在的时候返回新链表的head结点

注意：
1.如果想删除最后一个结点，p->next已经为空，不会再进入循环，无法删除。因此在每一步q连接新的结点后，尾部指向NULL，再进行下一步循环
2.不能直接在原链表上判断，如果与val值相等，跳到下一位。因为这样无法对头部元素和尾部元素进行循环，对于p->next和p->next->next是否存在还需要多重判断

----------------------------------------------
知识补充：
1.递归
递归，就是在运行的过程中调用自己。

构成递归需具备的条件：
a.子问题须与原始问题为同样的事，且更为简单；
b.不能无限制地调用本身，须有个出口，化简为非递归状况处理。
(一般来说，递归需要有边界条件、递归前进段和递归返回段。当边界条件不满足时，递归前进；当边界条件满足时，递归返回。)

递归的方法体现在内存上就是压栈和出栈，因此时间和空间消耗都比较大

2.尾递归
当递归调用是整个函数体中最后执行的语句且它的返回值不属于表达式的一部分时，这个递归调用就是尾递归。

当编译器检测到一个函数调用是尾递归的时候，它就覆盖当前的活动记录而不是在栈中去创建一个新的。
编译器可以做到这点，因为递归调用是当前活跃期内最后一条待执行的语句，于是当这个调用返回时栈帧中并没有其他事情可做，因此也就没有保存栈帧的必要了。
通过覆盖当前的栈帧而不是在其之上重新添加一个，这样所使用的栈空间就大大缩减了，这使得实际的运行效率会变得更高。

---------------------------------------------
本题使用的尾递归的方法：时间复杂度和上面相同
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
    ListNode* removeElements(ListNode* head, int val) {
        removehelper(head, val);
        return head;
    }
    
    void removehelper(ListNode *&head, int val){
        if(head == NULL){
            return;
        }
        if(head->val == val){
           ListNode *tmp = head->next;
           if (tmp){
                head->val = tmp->val;
                head->next = tmp->next;
                delete tmp;
            }else{
                delete head;
                head = NULL;
            }
            return removeElementsHelper(head, val);
        }
        return removehelper(head-> next, val);
    }
};
