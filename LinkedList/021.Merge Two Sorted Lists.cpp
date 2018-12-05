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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL && l2 == NULL) return NULL;
        ListNode newlist(0);
        ListNode *move = &newlist;
        ListNode *p = l1;
        ListNode *q = l2;
        
        while(p != NULL && q != NULL){
            if(p -> val >= q -> val){
                move -> next = q;
                move = move -> next;
                q = q-> next;
            }
            else{
                move -> next = p;
                move = move -> next;
                p = p->next;
            }
        }
        
        if(p == NULL && q != NULL){
            move -> next = q;
        }
        
        if(q == NULL && p != NULL){
            move -> next = p;
        }
        
        return newlist.next;
        
    }
};
/*
splice 拼接
设计思路：
1.建立一个新的链表
2.比较l1与l2的大小，谁小连谁
3.若长度不同，直接把长的链表结尾接过来

注意：
1.新建链表！！！
ListNode newlist(0)；ListNode *move = &newlist; 其中0也可以写成NULL。
2.返回链表的时候要是 结点.next
3.判断结尾的两个if,可以改成move ->next = l1 ? l1 :l2;【这一步思路比较简洁】
*/

12.4复习：
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *dummy = new ListNode(0);
        ListNode *cur = dummy;
        while(l1 && l2){
            if(l1 -> val <= l2 -> val){
                cur -> next = l1;
                l1 = l1 -> next;
            }else{
                cur -> next = l2;
                l2 = l2 -> next;
            }
            cur = cur -> next;
        }
        if(l1) cur -> next = l1;
        if(l2) cur -> next = l2;
        return dummy -> next;
    }
};
也可以是：
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(NULL);
        ListNode *cur = &dummy;
        while(l1 && l2){
            if(l1 -> val <= l2 -> val){
                cur -> next = l1;
                l1 = l1 -> next;
            }else{
                cur -> next = l2;
                l2 = l2 -> next;
            }
            cur = cur -> next;
        }
        if(l1) cur -> next = l1;
        if(l2) cur -> next = l2;
        return dummy.next;
    }
};
注意区别：
1.新建的dummy结点可以是一个指针类型，那么需要它赋值为0，用一个cur指针指向它可以移动。
最后返回的是dummy指针的下一位。
2.新建的dummy也可以只是一个结点，如果结点用一个指针指向它的时候就需要取它的地址。
最后返回的是结点的下一个元素，因为不是指针不能箭头指向，需要直接引用结构体中的next,即.next.