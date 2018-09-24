Iterative
T(n) = O(n);
S(n) = O(1);
思路：
1.因为实现链表反转，就可以从原链表的head结点开始，依次形成一个新的链表。原链表中后面的元素依次加在新链表的头部。
2.那么首先创建一个新的空结点，注意声明方式： ListNode *ret = NULL;
3.对原链表进行遍历，只要head结点存在，将其接在新链表的头部
4.共需要以下几个指针：
head：一直为原链表的头部结点，起到遍历和判断下一个结点是否存在的作用
now：因为head结点需要移动，为了把当前的结点接在新的链表头部，需要重新定义一个now结点来实现这一步。
     注意只要每次重新进入while循环，都需要重新声明
ret:新链表的头部结点，创建新链表的时候使用。now结点的next每次指向ret的头部结点。
    注意每次循环末尾都需要重新把ret指针置于新链表头部。
5.返回ret
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
    ListNode* reverseList(ListNode* head) {
        ListNode *ret = NULL;
        while(head){
            ListNode *now = head;
            head = head->next;
            now -> next = ret;
            ret = now;
        }
        return ret;
    }
};
----------------------------------------------
Recursion
T(n) = O(n);
S(n) = O(n);
思路：
1.问题分解为从原链表尾部开始，依次反转最后一个元素和倒数第二个元素
2.那么先将head指针移动到原链表最后（边界条件是head或者head->next不存在），定义p是倒数第二个元素
3.【巧妙点】p->next->next原本不存在，现在指向p,p->next指向NULL，反转了head 和 p
4.最后返回head
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head -> next) return head;
        ListNode *p = head;
        head = reverseList(head -> next);
        p -> next -> next = p;
        p -> next = NULL;
        
        return head;
    }
};
